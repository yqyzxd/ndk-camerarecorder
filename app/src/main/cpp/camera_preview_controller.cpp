//
// Created by 史浩 on 2023/5/5.
//

#include "camera_preview_controller.h"


void *CameraPreviewController::threadCallback(void *ctx) {
    CameraPreviewController* controller= static_cast<CameraPreviewController *>(ctx);
    controller->loop();
    return 0;
}

CameraPreviewController::CameraPreviewController() {


    handler=new CameraPreviewHandler(this);
    //启动渲染线程
    pthread_create(&threadId,0,threadCallback,this);
}

CameraPreviewController::~CameraPreviewController() {

}

void CameraPreviewController::loop() {

}
