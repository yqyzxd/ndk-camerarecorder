package com.wind.ndk.camera

import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.os.Message
import android.view.WindowMetrics
import androidx.appcompat.app.AppCompatActivity
import com.wind.ndk.camera.databinding.ActivityCameraPreviewBinding

class CameraPreviewActivity  : AppCompatActivity() {
    private lateinit var binding: ActivityCameraPreviewBinding
    private lateinit var scheduler:CameraPreviewScheduler
    private var mEncoding=false
    private val WHAT_UPDATE_TIME=102
    private var mDuration:Int=0
    private val mHandler=object :Handler(Looper.myLooper()!!){
        override fun handleMessage(msg: Message) {

            mDuration++
            val mins=mDuration/60
            val secs=mDuration%60

            val minsStr=if (mins<10){
                "0${mins}"
            }else "${mins}"

            val secsStr=if (secs<10){
                "0${secs}"
            }else "${secs}"
            binding.tvTime.text ="${minsStr}:${secsStr}"
            sendEmptyMessageDelayed(WHAT_UPDATE_TIME,1000)
        }
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityCameraPreviewBinding.inflate(layoutInflater)
        setContentView(binding.root)


        val previewView= CameraPreviewView(this)
        binding.root.addView(previewView,0)


        val params=previewView.layoutParams
        params.width=windowManager.defaultDisplay.width
        params.height=windowManager.defaultDisplay.width
        previewView.layoutParams=params

        val camera=VideoCamera(this)
        scheduler=CameraPreviewScheduler(previewView,camera)

        binding.btnSwitch.setOnClickListener {
            scheduler.switchCamera()
        }

        binding.btnEncode.setOnClickListener {
            if (mEncoding){
                mEncoding=false

                mHandler.removeCallbacksAndMessages(null)
                binding.tvTime.text ="00:00"
                scheduler.stopEncode()

            }else{
                mEncoding=true
                mDuration=0
                 /* resolution must be a multiple of two */
                //输出视频宽高注意与camera 宽高一样 ,不一致的话画面会花屏
                val width=720
                val height=1280
                val videoBitrate=720*1280*4
                val frameRate=24
                val h264File="${getExternalFilesDir(null)?.absolutePath}/camera_preview.h264"

                scheduler.startEncode(h264File,width,height,videoBitrate,frameRate)
                mHandler.sendEmptyMessageDelayed(WHAT_UPDATE_TIME,1000)
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        scheduler.release()
    }
}