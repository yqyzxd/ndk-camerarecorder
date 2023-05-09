//
// Created by 史浩 on 2023/5/7.
//

#ifndef NDK_CAMERARECORDER_GL_SHADERS_H
#define NDK_CAMERARECORDER_GL_SHADERS_H
#ifdef __cplusplus
extern "C" {
#endif

#define SHADER_STRING(s) #s

static char* base_vertex=SHADER_STRING(
            // 把顶点坐标给这个变量， 确定要画画的形状
            attribute vec4 a_Position;
            //接收纹理坐标，接收采样器采样图片的坐标
            attribute vec2 a_Coordinate;
            //传给片元着色器 像素点
            varying vec2 v_Coordinate;

            void main() {
                //内置变量 gl_Position ,我们把顶点数据赋值给这个变量 opengl就知道它要画什么形状了
                gl_Position = a_Position;
                v_Coordinate = a_Coordinate;
            }
        );

static char*  base_fragment= SHADER_STRING(
            //float数据是什么精度的
            precision mediump float;
            //采样点的坐标
            varying vec2 v_Coordinate;
            //采样器
            uniform sampler2D u_Texture;

            void main(){
                //变量 接收像素值
                // texture2D：采样器 采集v_Coordinate的像素
                //赋值给 gl_FragColor 就可以了
                gl_FragColor = texture2D(u_Texture, v_Coordinate);
            }
        );

#ifdef __cplusplus
};
#endif

#endif //NDK_CAMERARECORDER_GL_SHADERS_H
