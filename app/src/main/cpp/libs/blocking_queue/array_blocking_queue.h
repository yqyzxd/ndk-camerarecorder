//
// Created by 史浩 on 2023/5/10.
//

#ifndef NDK_CAMERARECORDER_ARRAY_BLOCKING_QUEUE_H
#define NDK_CAMERARECORDER_ARRAY_BLOCKING_QUEUE_H


#include "blocking_queue.h"
#include <climits>
class ArrayBlockingQueue : public BlockingQueue{
public:
    ArrayBlockingQueue(int size);
    ArrayBlockingQueue(): ArrayBlockingQueue(INT_MAX){};

};


#endif //NDK_CAMERARECORDER_ARRAY_BLOCKING_QUEUE_H
