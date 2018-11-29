#pragma once

#include "hxcpp.h"
#include "nanovg.h"

struct NVGcontext;
struct NVGtextRow;

namespace nanovg {
    NVGcontext* nvgCreateGL(int _flags);
    void nvgDeleteGL(NVGcontext* _ctx);
    float nvgTextBoundsHelper(NVGcontext* _ctx, float _x, float _y, String _string, String _end, Array<float> out);
    Array<Dynamic> nvgTextBreakLinesHelper(NVGcontext* ctx, String string, float breakRowWidth);
    void nvgTextBoxBoundsHelper(NVGcontext* _ctx, float _x, float _y, float _breakRowWidth, String _string, String _end, Array<float> out);
}
