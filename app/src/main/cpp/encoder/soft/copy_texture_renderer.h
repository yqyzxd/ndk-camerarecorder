//
// Created by 史浩 on 2023/5/11.
//

#ifndef NDK_CAMERARECORDER_COPY_TEXTURE_RENDERER_H
#define NDK_CAMERARECORDER_COPY_TEXTURE_RENDERER_H


#include "gles/base_filter.h"
#include "egl/gl_renderer.h"

class CopyTextureRenderer : public GLRenderer {
public:
    CopyTextureRenderer();

    ~CopyTextureRenderer();


    void surfaceCreated();
    void surfaceChanged(int width, int height);
    void surfaceDestroyed();
    void onDrawFrame();

private:
    BaseFilter *mFilter;

};


#endif //NDK_CAMERARECORDER_COPY_TEXTURE_RENDERER_H
