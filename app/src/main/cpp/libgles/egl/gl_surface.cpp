//
// Created by 史浩 on 2023/3/29.
//

#include "gl_surface.h"


#define LOG_TAG "GLSurface"
GLSurface::GLSurface() {
    mRenderMode=RENDER_MODE_WHEN_DIRTY;
    mRunnables=new std::queue<Runnable*>();
    pthread_mutex_init(&mLock,NULL);
    pthread_cond_init(&mCond,NULL);
}

GLSurface::~GLSurface() {
    delete mRunnables;
    mRunnables= nullptr;

    pthread_mutex_destroy(&mLock);
    pthread_cond_destroy(&mCond);
}

void *GLSurface::threadStartRoutine(void *myself) {
    GLSurface* glSurface= (GLSurface *)myself;
    glSurface->renderLoop();
    return 0;
}

void GLSurface::setRenderer(GLRenderer *renderer) {
    LOGI("setRenderer");
    this->mRenderer=renderer;
    if (mRenderThreadStarted){
        //already started
        return;
    }


    pthread_create(&_rendererThreadId,0,threadStartRoutine,this);
}

GLRenderer *GLSurface::getRenderer() {
    return mRenderer;
}

void GLSurface::surfaceCreated(ANativeWindow *window) {
    pthread_mutex_lock(&mLock);
    LOGI("surfaceCreated %d",mRenderThreadStarted);
    this->window=window;
    mSurfaceEvent=SURFACE_EVENT_CREATED;
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);
}

void GLSurface::surfaceChanged(int width, int height) {

    pthread_mutex_lock(&mLock);
    while (!mSurface&&mRenderer){
        //wait for surface
        pthread_cond_wait(&mCond,&mLock);
    }
    LOGE("surfaceChanged %d",mRenderThreadStarted);
    mSurfaceEvent=SURFACE_EVENT_CHANGED;
    mSurfaceWidth=width;
    mSurfaceHeight=height;
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);
}

void GLSurface::surfaceDestroyed() {
    pthread_mutex_lock(&mLock);
    LOGE("GLSurface::surfaceDestroyed");
    mSurfaceEvent=SURFACE_EVENT_DESTROYED;
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);

}

void GLSurface::queueEvent(Runnable* runnable) {
    pthread_mutex_lock(&mLock);

    mRunnables->push(runnable);
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);

}

void GLSurface::requestRender() {
    pthread_mutex_lock(&mLock);
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);
}

void GLSurface::dealloc() {
    LOGE("dealloc");
    pthread_mutex_lock(&mLock);
    releaseSurface();
    delete mRenderer;
    mRenderer=NULL;
    mKillRendererThread= true;
    pthread_cond_signal(&mCond);
    pthread_mutex_unlock(&mLock);
    LOGE("wait GL THREAD");
    //等待线程结束
    pthread_join(_rendererThreadId, 0);
    mRenderThreadStarted= false;

    LOGE("GL THREAD dead");
}
void GLSurface::renderLoop() {
    mRenderThreadStarted= true;

    while (!mKillRendererThread){
        mWakeUpFromDestoryed= false;
        pthread_mutex_lock(&mLock);
        switch (mSurfaceEvent) {
            case SURFACE_EVENT_CREATED:
                mSurfaceEvent=SURFACE_EVENT_NONE;
                if (mRenderer){
                    EGLCore* egl=new EGLCore();
                    egl->init();
                    mSurface=new WindowSurface(egl,window);
                    LOGI("makeCurrent before");
                    mSurface->makeCurrent();
                    LOGI("makeCurrent after");
                    LOGI("surfaceCreated before");
                    mRenderer->surfaceCreated();
                    LOGI("surfaceCreated after");
                    pthread_cond_signal(&mCond);
                }
                break;
            case SURFACE_EVENT_CHANGED:
                mSurfaceEvent=SURFACE_EVENT_NONE;
                if (mRenderer){
                    mSurface->makeCurrent();
                    mRenderer->surfaceChanged(mSurfaceWidth,mSurfaceHeight);

                }
                break;
            case SURFACE_EVENT_DESTROYED:
                mSurfaceEvent=SURFACE_EVENT_NONE;
                releaseSurface();
                //GL THREAD 进入等待状态，渲染线程依旧存在，当下次surfaceCreate时无须重启渲染线程
                LOGI("SURFACE_EVENT_DESTROYED before");
                pthread_cond_wait(&mCond,&mLock);
                mWakeUpFromDestoryed = true;
                LOGI("SURFACE_EVENT_DESTROYED after");
                break;
        }




        if (mRenderer && mSurface){
            while (!mRunnables->empty()){
                Runnable* runnable=mRunnables->front();
                mRunnables->pop();
                LOGI("GLSurface before run");
                runnable->run();
                delete runnable;
                runnable= NULL;
                LOGI("GLSurface after run");
            }
            mSurface->makeCurrent();
            LOGI("before onDrawFrame");
            mRenderer->onDrawFrame();
            LOGI("after onDrawFrame");
            mSurface->swapBuffers();
        }
        if (mRenderMode == RENDER_MODE_WHEN_DIRTY && !mKillRendererThread&& !mWakeUpFromDestoryed){
            LOGI("before pthread_cond_wait");
            pthread_cond_wait(&mCond,&mLock);
            LOGI("after pthread_cond_wait");
        }
        //LOGE("GL thread next loop");
        pthread_mutex_unlock(&mLock);
    }
}

void GLSurface::releaseSurface() {
    if (mRenderer){
        mRenderer->surfaceDestroyed();
    }
    if (mSurface){
        mSurface->release();
        delete mSurface;
        mSurface=NULL;
    }
}
