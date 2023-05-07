//
// Created by 史浩 on 2023/5/6.
//

#ifndef NDK_CAMERARECORDER_BASE_FBO_FILTER_H
#define NDK_CAMERARECORDER_BASE_FBO_FILTER_H


#include "base_filter.h"

class BaseFboFilter: public BaseFilter{
private:
    GLuint fbo;
    GLuint fboTextureId;
public:
    BaseFboFilter(const char *vertexSource, const char *fragmentSource);
    virtual ~BaseFboFilter();
    virtual void onReady(int width,int height);
    virtual GLuint onDrawFrame(GLuint textureId);
    virtual void dealloc();


};


#endif //NDK_CAMERARECORDER_BASE_FBO_FILTER_H
