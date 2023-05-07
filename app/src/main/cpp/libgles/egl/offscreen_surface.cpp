//
// Created by 史浩 on 2023/3/29.
//

#include "offscreen_surface.h"

OffscreenSurface::OffscreenSurface(EGLCore *eglCore,int width,int height) : BaseEGLSurface(eglCore) {


    createOffscreenSurface(width,height);
}


void OffscreenSurface::release() {
    releaseEglSurface();
}