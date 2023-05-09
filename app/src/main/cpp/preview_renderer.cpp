//
// Created by 史浩 on 2023/5/6.
//

#include "preview_renderer.h"
#include "gles/gl_utils.h"


#define  LOG_TAG "PreviewRenderer"
PreviewRenderer::PreviewRenderer(JavaVM*javaVm,jobject jobj,int cameraFacingId) {
    mCameraFacingId=cameraFacingId;
    mCaller=new CameraPreviewSchedulerCaller(javaVm,jobj);

}

PreviewRenderer::~PreviewRenderer() {
    if (mCaller){
        delete mCaller;
        mCaller= nullptr;
    }

    if (mTexture){
        mTexture->dealloc();
        delete mTexture;
        mTexture= nullptr;
    }

    if (mCameraFilter){
        mCameraFilter->dealloc();
        delete mCameraFilter;
        mCameraFilter= nullptr;
    }
    if (mScreenFilter){
        mScreenFilter->dealloc();
        delete mScreenFilter;
        mScreenFilter= nullptr;
    }
}

void PreviewRenderer::surfaceCreated() {

    mTexture=new Texture(GL_TEXTURE_EXTERNAL_OES);
    mTexture->createTexture();
    mCameraFilter=new CameraFilter();
    mScreenFilter=new ScreenFilter();
    LOGI("before startPreview");
    startPreview(mCameraFacingId);
    LOGI("after startPreview");

}


void PreviewRenderer::startPreview(int cameraFacingId) {
    mCaller->releaseCamera();
    CameraInfo* cameraInfo=mCaller->configCamera(cameraFacingId);
    mTextureWidth=cameraInfo->previewWidth;
    mTextureHeight=cameraInfo->previewHeight;
    checkGlError("createTexture");
    mCaller->startPreview(mTexture->getTextureId());

    if (mCameraFacingId==1){ //前置摄像头
        mScreenFilter->setTextureSize(mTextureHeight,mTextureWidth);
    }else{
        mScreenFilter->setTextureSize(mTextureWidth,mTextureHeight);
    }

}


void PreviewRenderer::surfaceChanged(int width, int height) {
    mCameraFilter->onReady(width,height);
    mScreenFilter->onReady(width,height);
}

void PreviewRenderer::onDrawFrame() {
    checkGlError("onDrawFrame");

    int textureId=mCameraFilter->onDrawFrame(mTexture->getTextureId());
    mScreenFilter->onDrawFrame(textureId);



}
void PreviewRenderer::surfaceDestroyed() {

    mCameraFilter->dealloc();
    mScreenFilter->dealloc();

    //通知java层释放camera
    mCaller->releaseCamera();
}

void PreviewRenderer::updateTexImage() {
    //checkGlError("updateTexImage");
    GLfloat* matrix=mCaller->updateTexImage();
    mCameraFilter->setMatrix(matrix);
}


