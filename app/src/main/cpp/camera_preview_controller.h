//
// Created by 史浩 on 2023/5/5.
//

#ifndef NDK_CAMERARECORDER_CAMERA_PREVIEW_CONTROLLER_H
#define NDK_CAMERARECORDER_CAMERA_PREVIEW_CONTROLLER_H

#include "message_queue/handler.h"
#include "egl_core/egl_core.h"

class CameraPreviewHandler;
class CameraPreviewController {
public:
    CameraPreviewController();
    ~CameraPreviewController();

    static void* threadCallback(void* ctx);
private:
    EGLCore* eglCore;

    CameraPreviewHandler* handler;

    pthread_t threadId;

    void loop();
};

class CameraPreviewHandler : Handler{

public:
    CameraPreviewHandler(CameraPreviewController *target){
        this->target=target;
    }
    void handleMessage(Message *msg) override{
        switch (msg->getWhat()) {

        }
    }
private:
    CameraPreviewController *target;

};


#endif //NDK_CAMERARECORDER_CAMERA_PREVIEW_CONTROLLER_H
