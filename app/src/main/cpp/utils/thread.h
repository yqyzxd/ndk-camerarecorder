//
// Created by wind on 2023/5/6.
//

#ifndef NDK_HANDLER_THREAD_H
#define NDK_HANDLER_THREAD_H
#include <pthread.h>

void* threadCallback(void* ctx);

class Thread {

public:
    Thread();
    virtual ~Thread()=0;

    /**启动线程*/
    virtual void start();

    /**线程函数*/
    virtual void run()=0;

private:
    pthread_t threadId;

   friend void* threadCallback(void* ctx);
};


#endif //NDK_HANDLER_THREAD_H
