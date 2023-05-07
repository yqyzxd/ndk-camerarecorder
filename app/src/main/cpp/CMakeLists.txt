cmake_minimum_required(VERSION 3.22.1)

project("camera")


include_directories(handler)
add_subdirectory(handler)

include_directories(libgles)
add_subdirectory(libgles)

add_library( # Sets the name of the library.
        camera

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        com_wind_ndk_camera_CameraPreviewScheduler.cpp
        camera_preview_controller.cpp
        camera_filter.cpp
        preview_renderer.cpp
        screen_filter.cpp

        camera_preview_scheduler_caller.cpp
        camera_info.cpp
        )


target_link_libraries( # Specifies the target library.
        camera

        # Links the target library to the log library
        # included in the NDK.
        handler
        log
        android
        eglcore
        )