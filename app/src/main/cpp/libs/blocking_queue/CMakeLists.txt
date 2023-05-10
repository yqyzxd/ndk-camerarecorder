cmake_minimum_required(VERSION 3.22.1)

project("blockingqueue")

include_directories(../lock)
add_subdirectory(../lock)


add_library( # Sets the name of the library.
        blockingqueue

        # Sets the library as a shared library.
        STATIC

        blocking_queue.cpp
        linked_blocking_queue.cpp
        array_blocking_queue.cpp

        )

target_link_libraries( # Specifies the target library.
        blockingqueue

        lock
        )