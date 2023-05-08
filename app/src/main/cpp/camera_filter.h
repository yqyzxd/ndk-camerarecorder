//
// Created by 史浩 on 2023/5/6.
//

#ifndef NDK_CAMERARECORDER_CAMERA_FILTER_H
#define NDK_CAMERARECORDER_CAMERA_FILTER_H


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "gles/base_fbo_filter.h"


static char* CAMERA_VERTEX_SHADER=
        "attribute vec4 a_Position;\n"
        "attribute vec4 a_Coordinate;\n"
        "varying vec2 v_Coordinate;\n"
        "uniform mat4 u_Matrix;\n"
        "void main(){\n"
        "   v_Coordinate= (u_Matrix*a_Coordinate).xy;\n"
        "   gl_Position=a_Position;\n"
        "}\n";

static char* CAMERA_FRAGMENT_SHADER=
        "#extension GL_OES_EGL_image_external : require\n"
        "precision mediump float;\n"
        "uniform samplerExternalOES u_Texture;\n"
        "varying vec2 v_Coordinate;\n"
        "void main(){\n"
        "   gl_FragColor=texture2D(u_Texture,v_Coordinate);"
        "}\n";


class CameraFilter : public BaseFboFilter{
private:
    GLuint uMatrixLocation;
    GLfloat* matrix = nullptr;
public:

    CameraFilter();
    ~CameraFilter();
    virtual GLuint getTextureTarget();
    /**获取AttributeLocation，UniformLocation等*/
    virtual void getLocation() override;
    /**填充AttributeLocation，UniformLocation等*/
    virtual void inflateLocation(GLuint textureId) override;
    /**获取顶点坐标*/
    //virtual GLfloat* getVertexData() override;
    /**获取纹理坐标*/
   // virtual GLfloat* getTextureData() override;

    void setMatrix(GLfloat* matrix);
};


#endif //NDK_CAMERARECORDER_CAMERA_FILTER_H
