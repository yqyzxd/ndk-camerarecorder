//
// Created by 史浩 on 2023/5/7.
//

#include "screen_filter.h"
ScreenFilter::ScreenFilter( char *vertexSource,  char *fragmentSource)
        : BaseFilter(vertexSource, fragmentSource) {

}

ScreenFilter::~ScreenFilter() {

}

void ScreenFilter::updateTexImage(GLuint textureId, void *bytes, int width, int height) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,bytes);

    glBindTexture(GL_TEXTURE_2D,0);
}