cmake_minimum_required(VERSION 3.22.1)

project("blockingqueue")

include_directories(../lock)
#原型add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
#lock不是当前目录的子目录，因此需要指定[binary_dir] 否则编译报错
add_subdirectory(../lock lock_binary_dir)

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