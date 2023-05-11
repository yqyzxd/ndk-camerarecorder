//
// Created by 史浩 on 2023/5/11.
//

#ifndef NDK_CAMERARECORDER_SOFT_ENCODER_ADAPTER_H
#define NDK_CAMERARECORDER_SOFT_ENCODER_ADAPTER_H

#include "../video_encoder_adapter.h"
#include "../../utils/thread.h"
#include "x264_encoder.h"
#include "../../libs/blocking_queue/linked_blocking_queue.h"
#include "../video_frame.h"
#include "egl/gl_offscreen_surface.h"

class SoftEncoderAdapter : public VideoEncoderAdapter {
public:
    SoftEncoderAdapter();

    ~SoftEncoderAdapter();

    void createEncoder(EGLContext sharedContext,int textureId);

    void encode();

    void dealloc();

    static void copyTextureRunnable(void* ctx);
    static void encodeRunnable(void* ctx);

    void runCopyTexture();
    void runEncode();
private:
    /**纹理拷贝线程*/
    Thread* mCopyThread;
    /**编码线程*/
    Thread* mEncodeThread;

    X264Encoder* mEncoder;

    BlockingQueue<VideoFrame*>* mVideoFrameQueue;

    GLOffScreenSurface* mGLOffScreenSurface;
};


#endif //NDK_CAMERARECORDER_SOFT_ENCODER_ADAPTER_H
