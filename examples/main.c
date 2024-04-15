#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_DISABLE_MATH
#include "pntr_app.h"

#define PNTR_PORTABLEGL_IMPLEMENTATION
#include "../pntr_portablegl.h"

typedef struct AppData {
    glContext* the_Context;
    unsigned int VBO, VAO;
    unsigned int shaderProgram;
} AppData;

bool Init(pntr_app* app) {
    AppData* appData = pntr_load_memory(sizeof(AppData));
    pntr_app_set_userdata(app, appData);

    // PortableGL setup
    appData->the_Context = pntr_init_glContext(app->screen);
	set_glContext(appData->the_Context);

	// build our shader program
	// ------------------------
	appData->shaderProgram = pglCreateProgram(basic_vs, basic_fs, 0, NULL, GL_FALSE);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left
		 0.5f, -0.5f, 0.0f, // right
		 0.0f,  0.5f, 0.0f  // top
	};

	glGenVertexArrays(1, &appData->VAO);
	glGenBuffers(1, &appData->VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(appData->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, appData->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
    AppData* appData = (AppData*)pntr_app_userdata(app);

    // Clear the background
    pntr_clear_background(screen, PNTR_RAYWHITE);

    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    //
    // Since we only have a single shader and a single VAO, there's really no need
    // to call UseProgram and BindVertexArray every time.  In fact, PGL supports
    // a default VAO (like compatibility profile), so you technically don't need
    // it at all in this case.  Same with shaders; I needed something to fill
    // index 0 so there is a default shader 0 which you can modify in portablegl.h
    // if you want, right now it just colors everything red with no transform
    glUseProgram(appData->shaderProgram);
    glBindVertexArray(appData->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    return true;
}

void Close(pntr_app* app) {
    AppData* appData = (AppData*)pntr_app_userdata(app);

	// PortableGL cleanup
	// ------------------------------------------------------------------
    glDeleteVertexArrays(1, &appData->VAO);
	glDeleteBuffers(1, &appData->VBO);
	glDeleteProgram(appData->shaderProgram);

	free_glContext(appData->the_Context);

    pntr_unload_memory(appData);
}

pntr_app Main(int argc, char* argv[]) {
    return (pntr_app) {
        .width = 640,
        .height = 480,
        .title = "pntr_app_starter",
        .init = Init,
        .update = Update,
        .close = Close,
        .fps = 60
    };
}
