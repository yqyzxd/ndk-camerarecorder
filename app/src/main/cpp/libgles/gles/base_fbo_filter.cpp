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
    checkGlError("createFrameBuffer");


}

GLuint BaseFboFilter::onDrawFrame(GLuint textureId) {
    glBindFramebuffer(GL_FRAMEBUFFER,fbo);
    glBindTexture(GL_TEXTURE_2D, fboTextureId);
    checkGlError("glBindTexture");
   // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,fboTextureId, 0);
  //  checkGlError("glFramebufferTexture2D");
    BaseFilter::onDrawFrame(textureId);
    checkGlError("after BaseFboFilter onDrawFrame");
    glBindTexture(GL_TEXTURE_2D, 0);
 //   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
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