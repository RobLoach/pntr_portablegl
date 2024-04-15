#ifndef PNTR_PORTABLEGL_H__
#define PNTR_PORTABLEGL_H__

#ifndef PGL_MALLOC
#define PGL_MALLOC(sz)      PNTR_MALLOC(sz)
#endif
#ifndef PGL_REALLOC
#define PGL_REALLOC(p, sz)  PNTR_REALLOC(p, sz)
#endif
#ifndef PGL_FREE
#define PGL_FREE(p)         PNTR_FREE(p)
#endif

#ifndef PNTR_PORTABLEGL_H
#define PNTR_PORTABLEGL_H "./vendor/portablegl.h"
#endif
#include PNTR_PORTABLEGL_H

glContext* pntr_init_glContext(pntr_image* screen);
void basic_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms);
void basic_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms);

#endif  // PNTR_PORTABLEGL_H__

#ifdef PNTR_PORTABLEGL_IMPLEMENTATION
#ifndef PNTR_PORTABLEGL_IMPLEMENTATION_ONCE
#define PNTR_PORTABLEGL_IMPLEMENTATION_ONCE

#define PORTABLEGL_IMPLEMENTATION
#include PNTR_PORTABLEGL_H

glContext* pntr_init_glContext(pntr_image* screen) {
    if (screen == NULL) {
        return NULL;
    }

    if (screen->subimage) {
        return NULL;
    }

    glContext* context = PNTR_MALLOC(sizeof(glContext));
    if (context == NULL) {
        return NULL;
    }

    #ifdef PNTR_PIXELFORMAT_RGBA
        u32 Rmask = 0xFF000000;
        u32 Gmask = 0x00FF0000;
        u32 Bmask = 0x0000FF00;
        u32 Amask = 0x000000FF;
    #elif defined(PNTR_PIXELFORMAT_ARGB)
        #if defined(SDL_BYTEORDER) && SDL_BYTEORDER == SDL_BIG_ENDIAN
            u32 Rmask = 0xFF000000;
            u32 Gmask = 0x00FF0000;
            u32 Bmask = 0x0000FF00;
            u32 Amask = 0x000000FF;
        #else
            u32 Rmask = 0x00FF0000;
            u32 Gmask = 0x0000FF00;
            u32 Bmask = 0x000000FF;
            u32 Amask = 0xFF000000;
        #endif
    #endif

    u32* backbuffer = (u32*)screen->data;
    if (!init_glContext(context, &backbuffer, screen->width, screen->height, sizeof(uint32_t), Rmask, Gmask, Bmask, Amask)) {
        PNTR_FREE(context);
        return NULL;
    }

    return context;
}

void basic_vs(float* vs_output, vec4* vertex_attribs, Shader_Builtins* builtins, void* uniforms)
{
	builtins->gl_Position = vertex_attribs[0];
}
void basic_fs(float* fs_input, Shader_Builtins* builtins, void* uniforms)
{
	builtins->gl_FragColor = make_vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

#endif  // PNTR_PORTABLEGL_IMPLEMENTATION_ONCE
#endif  // PNTR_PORTABLEGL_IMPLEMENTATION

