//
// Created by 史浩 on 2023/5/10.
//

#ifndef NDK_CAMERARECORDER_BLOCKING_QUEUE_H
#define NDK_CAMERARECORDER_BLOCKING_QUEUE_H

#include <climits>
#include <pthread.h>
#include "../lock/lock.h"

template<class T>
class BlockingQueue {
public:
    BlockingQueue(){};
    virtual ~BlockingQueue(){};
    /**
     * Inserts the specified element into this queue, waiting if necessary for space to become available.
     * @param elem
     */
    virtual int put(T elem)=0;
    /**
     * Retrieves and removes the head of this queue, waiting if necessary until an element becomes available.
     * @param elem  the head of this queue
     * @return
     */
    virtual int take(T* elem)=0;

};


#endif //NDK_CAMERARECORDER_BLOCKING_QUEUE_H
