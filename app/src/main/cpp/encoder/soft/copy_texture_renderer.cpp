//
// Created by 史浩 on 2023/5/11.
//

#include "copy_texture_renderer.h"


#define LOG_TAG "CopyTextureRenderer"
CopyTextureRenderer::CopyTextureRenderer(Callback callback,void* ctx) {
    this->mCallback=callback;
    this->mCallbackCtx=ctx;
}

CopyTextureRenderer::~CopyTextureRenderer() {
    mFboFilter->dealloc();
    delete mFboFilter;
    mFboFilter= nullptr;

    mYuy2Filter->dealloc();
    delete mYuy2Filter;
    mYuy2Filter= nullptr;
}

void CopyTextureRenderer::surfaceCreated() {
    mFboFilter=new BaseFboFilter();
    mYuy2Filter=new RgbToYuy2Filter();

    mTexture=new Texture();
    mTexture->createTexture();
}
void CopyTextureRenderer::surfaceChanged(int width, int height) {
    mFboFilter->onReady(width,height);
    mYuy2Filter->onReady(width,height);
    this->mWidth=width;
    this->mHeight=height;
}


void CopyTextureRenderer::updateTex(int textureId) {
    this->mInputTextureId=textureId;
}

void CopyTextureRenderer::onDrawFrame() {
    if (mInputTextureId<0){
        return;
    }
    LOGI("onDrawFrame");
    int textureId=mFboFilter->onDrawFrame(mInputTextureId);
    byte* bytes= new byte[mWidth*mHeight*4];
    // 将像素数据从显存拷贝到内存中
    mFboFilter->readPixels(bytes);//有数据
    mYuy2Filter->onDrawFrame(textureId);
    byte* bytes2= new byte[mWidth*mHeight*2];
    // 将像素数据从显存拷贝到内存中
    LOGI("before readPixels");
    mYuy2Filter->readPixels(bytes2);//无数据
    LOGI("after readPixels");
    this->mCallback(mCallbackCtx,new byte[mWidth*mHeight*2]);
    LOGI("after mCallback");

}
void CopyTextureRenderer::surfaceDestroyed() {}