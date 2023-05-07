package com.wind.ndk.camera

import android.os.Bundle
import android.os.Handler
import android.view.WindowMetrics
import androidx.appcompat.app.AppCompatActivity
import com.wind.ndk.camera.databinding.ActivityCameraPreviewBinding

class CameraPreviewActivity  : AppCompatActivity() {
    private lateinit var binding: ActivityCameraPreviewBinding
    private lateinit var scheduler:CameraPreviewScheduler
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityCameraPreviewBinding.inflate(layoutInflater)
        setContentView(binding.root)


        val previewView= CameraPreviewView(this)
        binding.root.addView(previewView,0)


        val params=previewView.layoutParams
        params.width=windowManager.defaultDisplay.width
        params.height=windowManager.defaultDisplay.height


        val camera=VideoCamera()
        scheduler=CameraPreviewScheduler(previewView,camera)

        binding.btnSwitch.setOnClickListener {

        }

    }
}