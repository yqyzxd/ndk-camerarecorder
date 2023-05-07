//
// Created by 史浩 on 2023/5/6.
//

#include "camera_filter.h"

CameraFilter::CameraFilter()
        : BaseFboFilter(CAMERA_VERTEX_SHADER, CAMERA_FRAGMENT_SHADER) {
}
CameraFilter::~CameraFilter() noexcept {

}

GLuint CameraFilter::getTextureTarget() {
    return GL_TEXTURE_EXTERNAL_OES;
}

void CameraFilter::getLocation() {
    BaseFboFilter::getLocation();
    uMatrixLocation= glGetUniformLocation(mProgram,"u_Matrix");
}

void CameraFilter::inflateLocation(GLuint textureId) {
    BaseFboFilter::inflateLocation(textureId);
    glUniformMatrix4fv(uMatrixLocation,1, GL_FALSE,matrix);
}

void CameraFilter::setMatrix(GLfloat *matrix) {
    this->matrix=matrix;
}
