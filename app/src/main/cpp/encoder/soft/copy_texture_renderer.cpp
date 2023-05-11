//
// Created by 史浩 on 2023/5/11.
//

#include "copy_texture_renderer.h"
CopyTextureRenderer::CopyTextureRenderer() {
    mFilter=new BaseFilter();
}

CopyTextureRenderer::~CopyTextureRenderer() {
    mFilter->dealloc();
    delete mFilter;
    mFilter= nullptr;
}

void CopyTextureRenderer::surfaceCreated() {}
void CopyTextureRenderer::surfaceChanged(int width, int height) {}

void CopyTextureRenderer::surfaceDestroyed() {}

void CopyTextureRenderer::onDrawFrame() {

}
