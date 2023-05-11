//
// Created by 史浩 on 2023/5/11.
//

#include "soft_encoder_adapter.h"


void SoftEncoderAdapter::copyTextureRunnable(void *ctx) {
    SoftEncoderAdapter *adapter = static_cast<SoftEncoderAdapter *>(ctx);
    adapter->runCopyTexture();

}

void SoftEncoderAdapter::encodeRunnable(void *ctx) {
    SoftEncoderAdapter *adapter = static_cast<SoftEncoderAdapter *>(ctx);
    adapter->runEncode();

}

SoftEncoderAdapter::SoftEncoderAdapter() {

    mCopyThread = new Thread(new Runnable(copyTextureRunnable, this));
    mEncodeThread = new Thread(new Runnable(encodeRunnable, this));
}

SoftEncoderAdapter::~SoftEncoderAdapter() noexcept {
    delete mCopyThread;
    delete mEncodeThread;
}


void SoftEncoderAdapter::runCopyTexture() {
    //拷贝纹理

}

void SoftEncoderAdapter::runEncode() {


}

void SoftEncoderAdapter::createEncoder(EGLContext sharedContext, int textureId) {
    //创建软件编码器，并且启动纹理拷贝线程和编码线程
    mGLOffScreenSurface = new GLOffScreenSurface(sharedContext, width, height);
    mGLOffScreenSurface->setRenderer();


    mEncoder = new X264Encoder();
    //创建VideoFrame阻塞队列
    mVideoFrameQueue = new LinkedBlockingQueue<VideoFrame *>();
    mCopyThread->start();
    mEncodeThread->start();
}

void SoftEncoderAdapter::encode() {
    //阻塞预览线程，待纹理拷贝线程拷贝成功之后继续预览
}

void SoftEncoderAdapter::dealloc() {

}