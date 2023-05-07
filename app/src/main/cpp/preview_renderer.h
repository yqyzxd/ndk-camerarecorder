//
// Created by 史浩 on 2023/5/6.
//

#ifndef NDK_CAMERARECORDER_PREVIEW_RENDERER_H
#define NDK_CAMERARECORDER_PREVIEW_RENDERER_H

#include "gles/gl_shaders.h"
#include "libgles/egl/gl_renderer.h"
#include "camera_filter.h"
#include "camera_preview_scheduler_caller.h"
#include "gles/texture.h"
#include "screen_filter.h"
class PreviewRenderer: public GLRenderer{
private:
    CameraFilter* mCameraFilter;
    ScreenFilter* mScreenFilter;
    CameraPreviewSchedulerCaller* mCaller;
    int mCameraFacingId;

    Texture* mTexture;
    int mTextureWidth;
    int mTextureHeight;
public:
    PreviewRenderer(JavaVM* javaVM,jobject jobj,int cameraFacingId);
    ~PreviewRenderer();
    void surfaceCreated() override;
    void surfaceChanged(int width, int height) override;
    void surfaceDestroyed() override;
    void onDrawFrame() override;

    void updateTexImage();
};


#endif //NDK_CAMERARECORDER_PREVIEW_RENDERER_H
