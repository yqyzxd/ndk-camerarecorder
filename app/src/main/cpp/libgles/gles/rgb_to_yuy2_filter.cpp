//
// Created by 史浩 on 2023/5/13.
//

#include "rgb_to_yuy2_filter.h"
#define LOG_TAG "RgbToYuy2Filter"
RgbToYuy2Filter::RgbToYuy2Filter(): BaseFboFilter(base_vertex,rgba_to_yuy2_fragment) {

    mUniformCoefficientY= glGetUniformLocation(mProgram,"u_CoefficientY");
    mUniformCoefficientU= glGetUniformLocation(mProgram,"u_CoefficientU");
    mUniformCoefficientV= glGetUniformLocation(mProgram,"u_CoefficientV");
    mUniformStep= glGetUniformLocation(mProgram,"u_Step");
    LOGI("mUniformCoefficientY:%d,mUniformCoefficientU:%d,mUniformCoefficientV:%d,mUniformStep:%d",mUniformCoefficientY,mCoordLocation,mUniformCoefficientV,mUniformStep);
}
RgbToYuy2Filter::~RgbToYuy2Filter() {

}

void RgbToYuy2Filter::onReady(int width, int height) {
    mSrcWidth=width;
    int yuy2Width=(width + 1) / 2;
    BaseFboFilter::onReady(yuy2Width,height);



}

void RgbToYuy2Filter::inflateLocation(GLuint textureId) {
    GLfloat coefficientY[4] ={COEFFICIENT_R_Y,COEFFICIENT_G_Y,COEFFICIENT_B_Y,16/(GLfloat)255};
    GLfloat coefficientU[4] ={COEFFICIENT_R_U,COEFFICIENT_G_U,COEFFICIENT_B_U,128/(GLfloat)255};
    GLfloat coefficientV[4] ={COEFFICIENT_R_V,COEFFICIENT_G_V,COEFFICIENT_B_V,128/(GLfloat)255};
    glUniform4fv(mUniformCoefficientY,1,coefficientY);
    glUniform4fv(mUniformCoefficientU,1,coefficientU);
    glUniform4fv(mUniformCoefficientV,1,coefficientV);
    checkGlError("glUniform1f mUniformCoefficientV");

    float step=1/(float)mSrcWidth;
    glUniform1f(mUniformStep,step);
    checkGlError("glUniform1f mUniformStep");
}


