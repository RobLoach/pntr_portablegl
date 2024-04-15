#ifndef PNTR_PORTABLEGL_H__
#define PNTR_PORTABLEGL_H__

#ifndef PGL_MALLOC
#define PGL_MALLOC(sz)      PNTR_MALLOC(sz)
#endif  // PGL_MALLOC

#ifndef PGL_REALLOC
#define PGL_REALLOC(p, sz)  PNTR_REALLOC(p, sz)
#endif  // PGL_REALLOC

#ifndef PGL_FREE
#define PGL_FREE(p)         PNTR_FREE(p)
#endif  // PGL_FREE

#ifndef PGL_MEMMOVE
#define PGL_MEMMOVE(dest, src, n) PNTR_MEMCPY((dest), (src), (n))
#endif  // PGL_MEMMOVE

// Prefix all types with 'pgl_'
#define PGL_PREFIX_TYPES

#ifndef PNTR_PORTABLEGL_H
#define PNTR_PORTABLEGL_H "./vendor/portablegl.h"
#endif

#include PNTR_PORTABLEGL_H

/**
 * Initialize the OpenGL context for the given destination image.
 *
 * @param dst The destination image to initialize the OpenGL context for.
 *
 * @return The initialized OpenGL context, or NULL on failure.
 */
glContext* pntr_init_glContext(pntr_image* dst);

#endif  // PNTR_PORTABLEGL_H__

#ifdef PNTR_PORTABLEGL_IMPLEMENTATION
#ifndef PNTR_PORTABLEGL_IMPLEMENTATION_ONCE
#define PNTR_PORTABLEGL_IMPLEMENTATION_ONCE

#define PORTABLEGL_IMPLEMENTATION
#include PNTR_PORTABLEGL_H

glContext* pntr_init_glContext(pntr_image* dst) {
    if (dst == NULL) {
        return NULL;
    }

    if (dst->subimage) {
        return NULL;
    }

    glContext* context = PNTR_MALLOC(sizeof(glContext));
    if (context == NULL) {
        return NULL;
    }

    #ifdef PNTR_PIXELFORMAT_RGBA
        // TODO: PortableGL - Fix the RGBA mask?
        u32 Rmask = 0x000000FF;
        u32 Gmask = 0x0000FF00;
        u32 Bmask = 0x00FF0000;
        u32 Amask = 0xFF000000;
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

    u32* backbuffer = (u32*)dst->data;
    if (!init_glContext(context, &backbuffer, dst->width, dst->height, 32, Rmask, Gmask, Bmask, Amask)) {
        PNTR_FREE(context);
        return NULL;
    }

    return context;
}

#endif  // PNTR_PORTABLEGL_IMPLEMENTATION_ONCE
#endif  // PNTR_PORTABLEGL_IMPLEMENTATION

