package com.wind.ndk.camera

import android.view.Surface

class CameraPreviewScheduler(surfaceView:CameraPreviewView) : CameraPreviewView.Callback {

    init {
        surfaceView.setCallback(this)
    }

    override fun onSurfaceCreated(surface: Surface) {
        nativeOnSurfaceCreated(surface)
    }



    override fun onSurfaceChanged(width: Int, height: Int) {
        nativeOnSurfaceChanged(width,height)
    }

    override fun onSurfaceDestroyed() {
        nativeOnSurfaceDestroyed()
    }



    private external fun nativeOnSurfaceCreated(surface: Surface)
    private external fun nativeOnSurfaceChanged(width: Int, height: Int)
    private external fun nativeOnSurfaceDestroyed()

}