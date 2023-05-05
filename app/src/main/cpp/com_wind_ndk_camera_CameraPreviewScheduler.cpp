//
// Created by 史浩 on 2023/5/5.
//
#include "com_wind_ndk_camera_CameraPreviewScheduler.h"
#include <jni.h>

JNIEXPORT void JNICALL
Java_com_wind_ndk_camera_CameraPreviewScheduler_nativeOnSurfaceCreated(JNIEnv* env,jobject thiz, jobject surface) {

}


JNIEXPORT void JNICALL
Java_com_wind_ndk_camera_CameraPreviewScheduler_nativeOnSurfaceChanged(JNIEnv* env,jobject thiz, jint width, jint height) {
// TODO: implement nativeOnSurfaceChanged()
}


JNIEXPORT void JNICALL
Java_com_wind_ndk_camera_CameraPreviewScheduler_nativeOnSurfaceDestroyed(JNIEnv* env,jobject thiz) {
// TODO: implement nativeOnSurfaceDestroyed()
}