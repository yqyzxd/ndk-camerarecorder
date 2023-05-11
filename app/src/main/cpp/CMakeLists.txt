cmake_minimum_required(VERSION 3.22.1)

project("camera")


include_directories(libs/handler)
add_subdirectory(libs/handler)

include_directories(libgles)
add_subdirectory(libgles)


include_directories(libs/blocking_queue)
add_subdirectory(libs/blocking_queue)

add_library( # Sets the name of the library.
        camera

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        com_wind_ndk_camera_CameraPreviewScheduler.cpp
        camera_preview_controller.cpp
        camera_preview/camera_filter.cpp
        camera_preview/preview_renderer.cpp
        camera_preview/screen_filter.cpp

        camera_preview_scheduler_caller.cpp
        camera_preview/camera_info.cpp

        encoder/video_frame.cpp
        encoder/video_encoder_adapter.cpp
        encoder/soft/soft_encoder_adapter.cpp
        encoder/soft/x264_encoder.cpp
        encoder/soft/copy_texture_renderer.cpp
        )


target_link_libraries( # Specifies the target library.
        camera

        # Links the target library to the log library
        # included in the NDK.
        libs/handler
        log
        android
        eglcore
        )