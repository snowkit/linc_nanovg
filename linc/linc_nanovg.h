#pragma once

#include "nanovg.h"

struct NVGcontext;

namespace nanovg {
    NVGcontext* nvgCreateGL(int _flags);
    void nvgDeleteGL(NVGcontext* _ctx);
}
