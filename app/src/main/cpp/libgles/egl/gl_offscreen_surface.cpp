//
// Created by 史浩 on 2023/5/11.
//

#include "gl_offscreen_surface.h"
GLOffScreenSurface::GLOffScreenSurface(EGLContext sharedContext, int width, int height) : GLSurface(sharedContext){
    this->width=width;
    this->height=height;
}
BaseEGLSurface *GLOffScreenSurface::createEGLSurface() {
    EGLCore* egl=new EGLCore();
    egl->init(mSharedContext);
    return new OffScreenSurface(egl,width,height);
}