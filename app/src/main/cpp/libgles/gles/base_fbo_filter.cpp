//
// Created by 史浩 on 2023/5/6.
//

#include "base_fbo_filter.h"
#include "gl_utils.h"

BaseFboFilter::BaseFboFilter(const char *vertexSource, const char *fragmentSource)
        : BaseFilter(vertexSource, fragmentSource) {

}

BaseFboFilter::~BaseFboFilter(){

}

void BaseFboFilter::onReady(int width, int height) {
    BaseFilter::onReady(width,height);

    createFrameBuffer(&fbo,&fboTextureId,width,height);



}

GLuint BaseFboFilter::onDrawFrame(GLuint textureId) {
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
    BaseFilter::onDrawFrame(textureId);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    return fboTextureId;
}

void BaseFboFilter::dealloc() {
    BaseFilter::dealloc();
    if (fboTextureId){
        glDeleteTextures(1,&fboTextureId);
        fboTextureId=0;
    }
    if (fbo){
        glDeleteFramebuffers(1,&fbo);
        fbo=0;
    }

}