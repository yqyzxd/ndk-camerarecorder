package com.wind.ndk.camera

import android.graphics.ImageFormat
import android.graphics.SurfaceTexture
import android.hardware.Camera
import android.hardware.Camera.CameraInfo

class VideoCamera {

    private var mCamera: Camera? = null
    private var mSurfaceTexture: SurfaceTexture? = null

    private var mCallback:Callback?=null
    private var mVideoWidth = VIDEO_WIDTH_1280
    private var mVideoHeight = VIDEO_HEIGHT_720


    fun configure(cameraFacingId: Int) :com.wind.ndk.camera.CameraInfo{
        if (mCamera != null) {
            releaseCamera()
        }
        try {
            mCamera = Camera.open(cameraFacingId)
            val parameters = mCamera?.parameters
            parameters?.apply {
                val supportedFormats = supportedPreviewFormats
                if (supportedFormats.contains(ImageFormat.NV21)) {
                    previewFormat = ImageFormat.NV21
                } else {
                    throw CameraException("preview format error")
                }

                if (isSupportedSize(supportedPreviewSizes, mVideoWidth, mVideoHeight)) {
                    setPreviewSize(mVideoWidth, mVideoHeight)
                } else {
                    mVideoWidth = VIDEO_WIDTH_640
                    mVideoHeight = VIDEO_HEIGHT_480
                    if (isSupportedSize(supportedPreviewSizes, mVideoWidth, mVideoHeight)) {
                        setPreviewSize(mVideoWidth, mVideoHeight)
                    } else {
                        throw CameraException("preview size error")
                    }

                }

                if (supportedFocusModes.contains(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO)) {
                    focusMode = Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO
                }


            }
            mCamera?.parameters=parameters


            return CameraInfo(mVideoWidth,mVideoHeight, getCameraFacing(cameraFacingId))
        } catch (e: Exception) {
           throw CameraException(e.message?:"")
        }
    }


    private fun isSupportedSize(sizes: List<Camera.Size>, width: Int, height: Int): Boolean {
        var supported = false;
        sizes.forEach {
            if (it.width == width && it.height == height) {
                supported = true
            }
        }
        return supported
    }

    private fun releaseCamera() {
        mSurfaceTexture?.release()
        mSurfaceTexture = null

        mCamera?.release()
        mCamera = null


    }

    fun setPreviewTexture(textureId: Int) {

        mCamera?.apply {
            mSurfaceTexture= SurfaceTexture(textureId)
            setPreviewTexture(mSurfaceTexture)
            mSurfaceTexture?.setOnFrameAvailableListener {
                mCallback?.onFrameAvailable()
            }
        }

    }

    fun startPreview() {
        mCamera?.startPreview()
    }

    companion object {
        val VIDEO_WIDTH_640 = 640
        val VIDEO_HEIGHT_480 = 480

        val VIDEO_WIDTH_1280 = 1280
        val VIDEO_HEIGHT_720 = 720

        @JvmStatic
        fun getCameraFacing(cameraId:Int):Int{
            var facing =0
            val cameraInfo=CameraInfo()
            Camera.getCameraInfo(cameraId,cameraInfo)
            if (cameraInfo.facing==Camera.CameraInfo.CAMERA_FACING_FRONT){
                facing=1
            }
            return facing
        }

    }
    fun setCallback(callback: Callback){
        this.mCallback=callback
    }

    fun updateTexImage(): FloatArray {
        var arr= floatArrayOf(
            1f,0f,0f,0f,
            0f,1f,0f,0f,
            0f,0f,1f,0f,
            0f,0f,0f,1f,
            )
        mSurfaceTexture?.updateTexImage()
        mSurfaceTexture?.getTransformMatrix(arr)

        return arr
    }

    interface Callback{
        fun onFrameAvailable()
    }
}