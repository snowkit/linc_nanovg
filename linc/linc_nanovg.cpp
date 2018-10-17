#include <hxcpp.h>

#include <GL/glew.h>

#include "nanovg.h"
#include "nanovg_gl.h"

namespace nanovg {

    NVGcontext* nvgCreateGL(int _flags) {
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            printf("Could not init glew.\n");
        }

        NVGcontext* ctx = 
        #if NANOVG_GL2_IMPLEMENTATION
            nvgCreateGL2(_flags);
        #elif NANOVG_GL3_IMPLEMENTATION
            nvgCreateGL3(_flags);
        #elif NANOVG_GL2ES_IMPLEMENTATION
            nvgCreateGL2ES(_flags);
        #elif NANOVG_GL3ES_IMPLEMENTATION
            nvgCreateGL3ES(_flags);
        #endif

        return ctx;
    }

    void nvgDeleteGL(NVGcontext* _ctx) {
        #if NANOVG_GL2_IMPLEMENTATION
            nvgDeleteGL2(_ctx);
        #elif NANOVG_GL3_IMPLEMENTATION
            nvgDeleteGL3(_ctx);
        #elif NANOVG_GL2ES_IMPLEMENTATION
            nvgDeleteGL2ES(_ctx);
        #elif NANOVG_GL3ES_IMPLEMENTATION
            nvgDeleteGL3ES(_ctx);
        #endif
    }

    Array<float> nvgTextBoundsHelper(NVGcontext* _ctx, float _x, float _y, String _string, String _end) {
        Array<float> out = new Array_obj<float>(4, 0);
        nvgTextBounds(_ctx, _x, _y, _string.c_str(), _end.c_str(), (float*)out->getBase());
        return out;
    }

    Array<float> nvgTextBoxBoundsHelper(NVGcontext* _ctx, float _x, float _y, float _breakRowWidth, String _string, String _end) {
        Array<float> out = new Array_obj<float>(4, 0);
        nvgTextBoxBounds(_ctx, _x, _y, _breakRowWidth, _string.c_str(), _end.c_str(), (float*)out->getBase());
        return out;
    }
}