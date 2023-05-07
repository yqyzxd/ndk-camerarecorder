package com.wind.ndk.camera

import android.hardware.Camera
import android.view.Surface

class CameraPreviewScheduler(private val mSurfaceView:CameraPreviewView, private val mCamera:VideoCamera) : CameraPreviewView.Callback,
    VideoCamera.Callback {
    private var mCameraFacingId=Camera.CameraInfo.CAMERA_FACING_FRONT
    init {
        mSurfaceView.setCallback(this)
        mCamera.setCallback(this)
    }

    override fun onSurfaceCreated(surface: Surface) {
        nativeOnSurfaceCreated(surface,mCameraFacingId)
    }



    override fun onSurfaceChanged(width: Int, height: Int) {
        nativeOnSurfaceChanged(width,height)
    }

    override fun onSurfaceDestroyed() {
        nativeOnSurfaceDestroyed()
    }


    fun configCameraFromNative(cameraFacingId:Int):CameraInfo{
        mCameraFacingId=cameraFacingId
        return mCamera.configure(cameraFacingId)
    }

    fun startPreviewFromNative(textureId:Int){
        mCamera.setPreviewTexture(textureId)
        mCamera.startPreview()
    }
    fun updateTexImageFromNative():FloatArray{
        return mCamera.updateTexImage();
    }

    override fun onFrameAvailable() {
        nativeOnFrameAvailable()
    }



    private external fun nativeOnSurfaceCreated(surface: Surface,cameraFacingId: Int)
    private external fun nativeOnSurfaceChanged(width: Int, height: Int)
    private external fun nativeOnSurfaceDestroyed()
    private external fun nativeOnFrameAvailable()

    companion object{
        init {
            System.loadLibrary("camera")
        }
    }

}