//
// Created by 史浩 on 2023/5/7.
//

#ifndef NDK_CAMERARECORDER_SCREEN_FILTER_H
#define NDK_CAMERARECORDER_SCREEN_FILTER_H


#include "libgles/gles/base_filter.h"
class ScreenFilter: public BaseFilter{
public:
    ScreenFilter( char *vertexSource,  char *fragmentSource);
    ~ScreenFilter();
    void updateTexImage(GLuint textureId,void* bytes,int width,int height);
};


#endif //NDK_CAMERARECORDER_SCREEN_FILTER_H
