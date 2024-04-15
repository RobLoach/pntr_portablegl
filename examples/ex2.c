#define PNTR_APP_IMPLEMENTATION
#include "pntr_app.h"

#define PNTR_PORTABLEGL_IMPLEMENTATION
#include "../pntr_portablegl.h"

typedef struct AppData {
    glContext* context;
} AppData;

void smooth_vs(float* vs_output, pgl_vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms);
void smooth_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms);

bool Init(pntr_app* app) {
    AppData* appData = pntr_load_memory(sizeof(AppData));
    pntr_app_set_userdata(app, appData);

    // PortableGL setup
    appData->context = pntr_load_glContext(app->screen);

    // Set up the OpenGL state
	GLenum smooth[4] = { PGL_SMOOTH4 };

	float points_n_colors[] = {
		-0.5, -0.5, 0.0,
		 1.0,  0.0, 0.0,

		 0.5, -0.5, 0.0,
		 0.0,  1.0, 0.0,

		 0.0,  0.5, 0.0,
		 0.0,  0.0, 1.0
    };

	GLuint triangle;
	glGenBuffers(1, &triangle);
	glBindBuffer(GL_ARRAY_BUFFER, triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points_n_colors), points_n_colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, 0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*)(sizeof(float)*3));

	// Note, no uniforms used in these shaders so no need to set any
	GLuint myshader = pglCreateProgram(smooth_vs, smooth_fs, 4, smooth, GL_FALSE);
	glUseProgram(myshader);

    return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
    AppData* appData = (AppData*)pntr_app_userdata(app);

    // Draw the triangle
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    return true;
}

void Close(pntr_app* app) {
    AppData* appData = (AppData*)pntr_app_userdata(app);

	// PortableGL cleanup
	pntr_unload_glContext(appData->context);

    pntr_unload_memory(appData);
}

void smooth_vs(float* vs_output, pgl_vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms) {
	((pgl_vec4*)vs_output)[0] = vertex_attribs[4]; //color
	builtins->gl_Position = vertex_attribs[0];
}

void smooth_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms) {
	builtins->gl_FragColor = ((pgl_vec4*)fs_input)[0];
}

pntr_app Main(int argc, char* argv[]) {
    return (pntr_app) {
        .width = 640,
        .height = 480,
        .title = "pntr_portablegl",
        .init = Init,
        .update = Update,
        .close = Close,
        .fps = 60
    };
}
