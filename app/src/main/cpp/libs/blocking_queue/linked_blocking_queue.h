//
// Created by 史浩 on 2023/5/10.
//

#ifndef NDK_CAMERARECORDER_LINKED_BLOCKING_QUEUE_H
#define NDK_CAMERARECORDER_LINKED_BLOCKING_QUEUE_H


#include <queue>
#include "blocking_queue.h"
template<class N>
class Node {
public:
    Node(N item,Node<N>* next){
        this->item=item;
        this->next=next;
    }
    ~Node(){
    }
    N item;
    Node<N>* next= nullptr;
};

template<class T>
class LinkedBlockingQueue : public BlockingQueue<T> {
public:
    LinkedBlockingQueue(int capacity);
    LinkedBlockingQueue():LinkedBlockingQueue(INT_MAX){};
    ~LinkedBlockingQueue();

    int put(T elem) override;
    int take(T *elem) override;

private:
    Lock* mLock;
    Condition* mCond;
    //最多可以存放多少个元素
    int capacity;
    //当前元素个数
    int size;
    Node<T>* head= nullptr;
    Node<T>* last= nullptr;
};


#endif //NDK_CAMERARECORDER_LINKED_BLOCKING_QUEUE_H
