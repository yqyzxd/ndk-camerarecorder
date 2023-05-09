//
// Created by 史浩 on 2023/5/5.
//

#include "camera_preview_controller.h"
#define LOG_TAG "CameraPreviewController"
void CameraPreviewController::updateTexImage(void *ctx) {
    LOGI("before updateTexImage");
    CameraPreviewController* controller= static_cast<CameraPreviewController *>(ctx);
    PreviewRenderer*renderer= dynamic_cast<PreviewRenderer *>(controller->glSurface->getRenderer());
    renderer->updateTexImage();
    LOGI("after updateTexImage");

}

void CameraPreviewController::innerSwitchCamera(void *ctx) {
    CameraPreviewController* controller= static_cast<CameraPreviewController *>(ctx);
    PreviewRenderer*renderer= dynamic_cast<PreviewRenderer *>(controller->glSurface->getRenderer());
    renderer->startPreview(controller->cameraFacingId);
}


CameraPreviewController::CameraPreviewController(JavaVM *javaVM, jobject jobj,int cameraFacingId) {
    this->cameraFacingId=cameraFacingId;
    glSurface=new GLSurface;
    glSurface->setRenderer(new PreviewRenderer(javaVM,jobj,cameraFacingId));
}

CameraPreviewController::~CameraPreviewController() {
    glSurface->dealloc();
    delete glSurface;
    glSurface= nullptr;
}

void CameraPreviewController::onSurfaceCreated(ANativeWindow *window) {
    LOGI("onSurfaceCreated");
    glSurface->surfaceCreated(window);

}

void CameraPreviewController::onSurfaceChanged(int width, int height) {
    LOGI("surfaceChanged");
    glSurface->surfaceChanged(width,height);
}

void CameraPreviewController::onSurfaceDestroyed() {
    LOGI("surfaceDestroyed");
    glSurface->surfaceDestroyed();




}

void CameraPreviewController::onFrameAvailable() {
    LOGI("onFrameAvailable");
    glSurface->queueEvent(new Runnable(updateTexImage,this));

}

void CameraPreviewController::switchCamera(int cameraFacingId) {
    //todo 切换相机最好先暂定渲染onDrawFrame
    this->cameraFacingId=cameraFacingId;
    glSurface->queueEvent(new Runnable(innerSwitchCamera,this));

}





