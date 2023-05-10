//
// Created by 史浩 on 2023/5/10.
//

#include "linked_blocking_queue.h"
template<class T>
LinkedBlockingQueue<T>::LinkedBlockingQueue(int capacity) {
    this->capacity=capacity;
    mLock=new Lock();
    mCond= mLock->newCondition();
}
template<class T>
LinkedBlockingQueue<T>::~LinkedBlockingQueue() {
    delete head;
    delete last;
    delete mLock;
}

template<class T>
int LinkedBlockingQueue<T>::put(T elem) {
    mLock->lock();
    if (size>=capacity){
        mCond->await();
    }
    Node<T>* node=new Node<T>(elem, nullptr);
    if (head== nullptr){
        head=last=node;
    } else {
        last->next=node;
        last=node;
    }
    size++;
    mCond->signal();
    mLock->unlock();
    return 1;

}
template<class T>
int LinkedBlockingQueue<T>::take(T *elem) {
    mLock->lock();
    if (size<=0){
        mCond->await();
    }

    elem=head;
    head=head->next;
    size--;
    mCond->signal();
    mLock->unlock();
    return 1;
}