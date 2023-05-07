//
// Created by 史浩 on 2023/5/5.
//

#ifndef NDK_CAMERARECORDER_CAMERA_PREVIEW_CONTROLLER_H
#define NDK_CAMERARECORDER_CAMERA_PREVIEW_CONTROLLER_H

#include <jni.h>
#include <android/native_window.h>
#include "handler//handler.h"
#include "handler/loop_thread.h"
#include "egl/gl_surface.h"

#include "preview_renderer.h"


#define CAMERA_FACING_BACK	 0
#define CAMERA_FACING_FRONT	 1



class CameraPreviewHandler;
class CameraPreviewController {
public:
    CameraPreviewController(JavaVM* javaVM,jobject jobj,int cameraFacingId);
    ~CameraPreviewController();

    void onSurfaceCreated(ANativeWindow *window);

    void onSurfaceChanged(int width, int height);

    void onSurfaceDestroyed();

    static void updateTexImage(void *ctx);

    void onFrameAvailable();

private:

    GLSurface* glSurface;


};




#endif //NDK_CAMERARECORDER_CAMERA_PREVIEW_CONTROLLER_H
