package com.wind.ndk.camera

import android.app.Activity
import android.content.Intent
import android.content.pm.PackageManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import androidx.core.app.ActivityCompat
import com.wind.ndk.camera.databinding.ActivityMainBinding
import java.util.concurrent.BlockingQueue
import java.util.concurrent.locks.ReentrantLock

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)


        binding.btnPreview.setOnClickListener {
            if(ActivityCompat.checkSelfPermission(it.context,android.Manifest.permission.CAMERA)!=PackageManager.PERMISSION_GRANTED){
                ActivityCompat.requestPermissions(it.context as Activity, arrayOf(android.Manifest.permission.CAMERA),1)
                return@setOnClickListener
            }
            startActivity(Intent(it.context,CameraPreviewActivity::class.java))
        }


    }

}