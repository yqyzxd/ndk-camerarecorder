//
// Created by 史浩 on 2023/5/7.
//

#ifndef NDK_CAMERARECORDER_SCREEN_FILTER_H
#define NDK_CAMERARECORDER_SCREEN_FILTER_H


#include "libgles/gles/base_filter.h"
class ScreenFilter: public BaseFilter{
private:
    int mTextureWidth;
    int mTextureHeight;
public:
    ScreenFilter(int textureWidth,int textureHeight);
    ~ScreenFilter();
    //void updateTexImage(GLuint textureId,void* bytes,int width,int height);

    //为了纹理与视口的比例保持一致（这样才能避免纹理被拉伸），需要裁剪纹理坐标，因此重写
    GLfloat *getTextureData() override;
};


#endif //NDK_CAMERARECORDER_SCREEN_FILTER_H
