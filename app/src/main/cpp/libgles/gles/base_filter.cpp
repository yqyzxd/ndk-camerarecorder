//
// Created by 史浩 on 2023/3/29.
//

#include "base_filter.h"
#include "gl_utils.h"
#include "../../utils/log.h"

#define LOG_TAG "BaseFilter"
BaseFilter::BaseFilter(const char *vertexSource, const char *fragmentSource) {

    LOGI( "before createProgram");
    mProgram=createProgram(vertexSource,fragmentSource);
    LOGI( "after createProgram mProgram:%d",mProgram);
    checkGlError("createProgram");
    getLocation();
}

void BaseFilter::onReady(int width, int height) {
    mWidth=width;
    mHeight=height;
}

void BaseFilter::getLocation() {
    mPositionLocation= glGetAttribLocation(mProgram,"a_Position");
    mCoordLocation= glGetAttribLocation(mProgram,"a_Coordinate");
    mTextureLocation= glGetUniformLocation(mProgram,"u_Texture");
    LOGI("mPositionLocation:%d,mCoordLocation:%d,mTextureLocation:%d",mPositionLocation,mCoordLocation,mTextureLocation);
}

GLuint BaseFilter::onDrawFrame(GLuint textureId) {
    //1， 设置视窗
    glViewport(0, 0, mWidth, mHeight);
    //2，使用着色器程序
    glUseProgram(mProgram);


    inflateLocation(textureId);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    return textureId;
}

void BaseFilter::inflateLocation(GLuint textureId) {
    //1，顶点数据
    glVertexAttribPointer(mPositionLocation, 2, GL_FLOAT, false, 0, getVertexData());//传值
    //使能顶点缓冲区
    glEnableVertexAttribArray(mPositionLocation);

    //2，纹理坐标
    glVertexAttribPointer(mCoordLocation, 2, GL_FLOAT, false, 0, getTextureData());
    glEnableVertexAttribArray(mCoordLocation);

    //激活图层
    glActiveTexture(GL_TEXTURE0);
    //绑定
    glBindTexture(getTextureTarget(), textureId);
    //传递参数
    glUniform1i(mTextureLocation, 0);

}
GLuint BaseFilter::getTextureTarget() {
    return GL_TEXTURE_2D;
}

GLfloat *BaseFilter::getVertexData() {
    return new GLfloat[8]{
                -1.0f, -1.0f,
                1.0f, -1.0f,
                -1.0f, 1.0f,
                1.0f, 1.0f,
    };
}

GLfloat *BaseFilter::getTextureData() {
    return new GLfloat[8]{
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
    };
}

void BaseFilter::dealloc() {

    if (mProgram) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
}