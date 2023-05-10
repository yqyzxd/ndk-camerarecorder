//
// Created by 史浩 on 2023/5/6.
//

#include "camera_filter.h"
#include "gles/gl_utils.h"

#define LOG_TAG "CameraFilter"
CameraFilter::CameraFilter()
        : BaseFboFilter(CAMERA_VERTEX_SHADER, CAMERA_FRAGMENT_SHADER) {
    LOGI("CREATE CameraFilter");
    //为什么父类没有调用 getLocation方法
    getLocation();
}
CameraFilter::~CameraFilter() noexcept {

}

GLuint CameraFilter::getTextureTarget() {
    return GL_TEXTURE_EXTERNAL_OES;
}

void CameraFilter::getLocation() {
    BaseFboFilter::getLocation();
    uMatrixLocation= glGetUniformLocation(mProgram,"u_Matrix");
    LOGI("uMatrixLocation:%d",uMatrixLocation);
    checkGlError("glGetUniformLocation uMatrixLocation");
}

void CameraFilter::inflateLocation(GLuint textureId) {
    BaseFboFilter::inflateLocation(textureId);

    if (matrix== nullptr){
        matrix=new GLfloat[16]{
          1,0,0,0,
          0,1,0,0,
          0,0,1,0,
          0,0,0,1,
        };
    }
    glUniformMatrix4fv(uMatrixLocation,1, GL_FALSE,matrix);
    checkGlError("glUniformMatrix4fv uMatrixLocation");
}

void CameraFilter::setMatrix(GLfloat *matrix) {
    LOGI("setMatrix %x",matrix);
    this->matrix=matrix;
}
