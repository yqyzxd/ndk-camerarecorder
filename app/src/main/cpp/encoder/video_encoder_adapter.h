//
// Created by 史浩 on 2023/5/10.
//

#ifndef NDK_CAMERARECORDER_VIDEO_ENCODER_ADAPTER_H
#define NDK_CAMERARECORDER_VIDEO_ENCODER_ADAPTER_H


#include "../libgles/gles/gl_utils.h"
#include <stdio.h>
class VideoEncoderAdapter {
public:
    VideoEncoderAdapter();
    virtual ~VideoEncoderAdapter(){};

    virtual int init(char* output,int width,int height,int bitRate,int frameRate);
    virtual void createEncoder(int textureId)=0;
    virtual void encode()=0;
    virtual void dealloc()=0;

protected:
    FILE* h264File;
    int width;
    int height;
    int bitRate;
    int frameRate;
    int textureId;
};


#endif //NDK_CAMERARECORDER_VIDEO_ENCODER_ADAPTER_H
