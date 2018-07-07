//hxcpp include should be first
#include <hxcpp.h>

#if defined(NANOVG_GL2_IMPLEMENTATION) || defined(NANOVG_GL3_IMPLEMENTATION)
#define GLEW 1
#include <GL/glew.h>
#elif  defined NANOVG_GLES3_IMPLEMENTATION
#include <GLES3/gl3.h>
#elif defined NANOVG_GLES2_IMPLEMENTATION
#include <GLES2/gl2.h>
#endif
#include "nanovg.h"
#include "nanovg_gl.h"
#include "nanovg_gl_utils.h"

namespace nanovg {

    NVGcontext* nvgCreateGL(int _flags) {

        #if GLEW
            GLenum err = glewInit();
            if (err != GLEW_OK) {
                printf("Could not init glew.\n");
            }
        #endif

        NVGcontext* ctx = 
        #if NANOVG_GL2_IMPLEMENTATION
            nvgCreateGL2(_flags);
        #elif NANOVG_GL3_IMPLEMENTATION
            nvgCreateGL3(_flags);
        #elif NANOVG_GLES2_IMPLEMENTATION
            nvgCreateGLES2(_flags);
        #elif NANOVG_GLES3_IMPLEMENTATION
            nvgCreateGLES3(_flags);
        #endif

        return ctx;
    }

    void nvgDeleteGL(NVGcontext* _ctx) {
        #if NANOVG_GL2_IMPLEMENTATION
            nvgDeleteGL2(_ctx);
        #elif NANOVG_GL3_IMPLEMENTATION
            nvgDeleteGL3(_ctx);
        #elif NANOVG_GLES2_IMPLEMENTATION
            nvgDeleteGLES2(_ctx);
        #elif NANOVG_GLES3_IMPLEMENTATION
            nvgDeleteGLES3(_ctx);
        #endif
    }
}