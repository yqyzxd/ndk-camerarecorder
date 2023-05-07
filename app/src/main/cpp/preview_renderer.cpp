//
// Created by 史浩 on 2023/5/6.
//

#include "preview_renderer.h"



#define  LOG_TAG "PreviewRenderer"
PreviewRenderer::PreviewRenderer(JavaVM*javaVm,jobject jobj,int cameraFacingId) {
    mCameraFacingId=cameraFacingId;
    mCaller=new CameraPreviewSchedulerCaller(javaVm,jobj);

}

PreviewRenderer::~PreviewRenderer() {

}

void PreviewRenderer::surfaceCreated() {
    mTexture=new Texture();
    mTexture->createTexture();
    mCameraFilter=new CameraFilter();
    CameraInfo* cameraInfo=mCaller->configCamera(mCameraFacingId);
    mTextureWidth=cameraInfo->previewWidth;
    mTextureHeight=cameraInfo->previewHeight;
    mCaller->startPreview(mTexture->getTextureId());


    mScreenFilter=new ScreenFilter(base_vertex,base_fragment);
}

void PreviewRenderer::surfaceChanged(int width, int height) {
    mCameraFilter->onReady(width,height);
    mScreenFilter->onReady(width,height);
}

void PreviewRenderer::onDrawFrame() {
    LOGI("onDrawFrame");

    int textureId=mCameraFilter->onDrawFrame(mTexture->getTextureId());
    mScreenFilter->onDrawFrame(textureId);



}
void PreviewRenderer::surfaceDestroyed() {
    mCameraFilter->dealloc();
}

void PreviewRenderer::updateTexImage() {
    GLfloat* matrix=mCaller->updateTexImage();
    mCameraFilter->setMatrix(matrix);
}
