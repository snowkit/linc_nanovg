#pragma once

#include "hxcpp.h"
#include "nanovg.h"

struct NVGcontext;

namespace nanovg {
    NVGcontext* nvgCreateGL(int _flags);
    void nvgDeleteGL(NVGcontext* _ctx);
    Array<float> nvgTextBoxBoundsHelper(NVGcontext* _ctx, float _x, float _y, float _breakRowWidth, String _string, String _end);
    Array<float> nvgTextBoundsHelper(NVGcontext* _ctx, float _x, float _y, String _string, String _end);
}
