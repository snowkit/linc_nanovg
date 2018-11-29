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

    
    Array<Dynamic> nvgTextBreakLinesHelper(NVGcontext* ctx, String string, float breakRowWidth){
        Array<Dynamic> outArray = Array_obj<Dynamic>::__new(0, 1);
        NVGtextRow rows[3];
        const char* text = string.c_str();
        const char* start = text;
        const char* end = text + strlen(text);
        int nrows;
        int i;
        while ((nrows = nvgTextBreakLines(ctx, start, end, breakRowWidth, rows, 3))) {
            for (i = 0; i < nrows; i++) {
                NVGtextRow row = rows[i];
                hx::Anon result = hx::Anon_obj::Create();
                result->Add(HX_CSTRING("start"), row.start);
                result->Add(HX_CSTRING("end"), row.end);
                result->Add(HX_CSTRING("next"), row.next);
                result->Add(HX_CSTRING("width"), row.width);
                result->Add(HX_CSTRING("minx"), row.minx);
                result->Add(HX_CSTRING("maxx"), row.maxx);
                outArray->push(result);
            
            }
            // Keep going...
            start = rows[nrows-1].next;
        }
        return outArray;
    }

    float nvgTextBoundsHelper(NVGcontext* _ctx, float _x, float _y, String _string, String _end, Array<float> outArray) {
        return nvgTextBounds(_ctx, _x, _y, _string.c_str(), _end.c_str(), (float*)outArray->getBase());
    }

    void nvgTextBoxBoundsHelper(NVGcontext* _ctx, float _x, float _y, float _breakRowWidth, String _string, String _end, Array<float> out) {
        nvgTextBoxBounds(_ctx, _x, _y, _breakRowWidth, _string.c_str(), _end.c_str(), (float*)out->getBase());
    }
}