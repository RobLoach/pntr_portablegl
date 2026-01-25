#ifndef PNTR_PORTABLEGL_H__
#define PNTR_PORTABLEGL_H__

#ifndef PGL_MALLOC
#define PGL_MALLOC(sz)      PNTR_MALLOC(sz)
#endif  // PGL_MALLOC

#ifndef PGL_REALLOC
#define PGL_REALLOC(p, sz)  PNTR_REALLOC((p), (sz))
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
#define PNTR_PORTABLEGL_H "./vendor/portablegl/portablegl.h"
#endif

#include PNTR_PORTABLEGL_H

#ifndef PNTR_PORTABLEGL_API
#define PNTR_PORTABLEGL_API PNTR_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the OpenGL context for the given destination image.
 *
 * @param dst The destination image to initialize the OpenGL context for.
 *
 * @return The initialized OpenGL context, or NULL on failure.
 *
 * @see init_glContext()
 */
PNTR_PORTABLEGL_API glContext* pntr_load_glContext(pntr_image* dst);
PNTR_PORTABLEGL_API void pntr_unload_glContext(glContext* context);

#ifdef __cplusplus
}
#endif

#endif  // PNTR_PORTABLEGL_H__

#ifdef PNTR_PORTABLEGL_IMPLEMENTATION
#ifndef PNTR_PORTABLEGL_IMPLEMENTATION_ONCE
#define PNTR_PORTABLEGL_IMPLEMENTATION_ONCE

#ifdef PNTR_PIXELFORMAT_RGBA
    // Default
#elif defined(PNTR_PIXELFORMAT_ARGB)
    #if defined(SDL_BYTEORDER) && SDL_BYTEORDER == SDL_BIG_ENDIAN
        #define PGL_RGBA32
    #else
        #define PGL_ARGB32
    #endif
#endif

#define PORTABLEGL_IMPLEMENTATION
#include PNTR_PORTABLEGL_H

#ifdef __cplusplus
extern "C" {
#endif

PNTR_PORTABLEGL_API glContext* pntr_load_glContext(pntr_image* dst) {
    if (dst == NULL || dst->subimage) {
        return NULL;
    }

    // Create the memory for the glContext.
    glContext* context = (glContext*)PNTR_MALLOC(sizeof(glContext));
    if (context == NULL) {
        return NULL;
    }

    // Create the context.
    u32* backbuffer = (u32*)dst->data;
    if (!init_glContext(context, &backbuffer, dst->width, dst->height)) {
        PNTR_FREE(context);
        return NULL;
    }

    // Set the active context.
    set_glContext(context);

    return context;
}

PNTR_PORTABLEGL_API void pntr_unload_glContext(glContext* context) {
    if (context == NULL) {
        return;
    }

    free_glContext(context);
    PNTR_FREE(context);
}

#ifdef __cplusplus
}
#endif

#endif  // PNTR_PORTABLEGL_IMPLEMENTATION_ONCE
#endif  // PNTR_PORTABLEGL_IMPLEMENTATION

