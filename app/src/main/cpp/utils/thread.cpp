//
// Created by wind on 2023/5/6.
//

#include "thread.h"

Thread::Thread() {

}
Thread::~Thread() {

}

void *threadCallback(void *ctx) {
    Thread* thread=(Thread*)ctx;
    thread->run();
    return 0;
}

void Thread::start() {
    pthread_create(&threadId,0,threadCallback,this);
}