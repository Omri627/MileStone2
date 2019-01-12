//
// Created by ranraboh on 12/01/19.
//

#ifndef PROJECT2_THREADPOOL_H
#define PROJECT2_THREADPOOL_H

#include <functional>
#include <queue>
#include "pthread.h"
using namespace std;
class ThreadPool {
public:
    enum operation_type {
        DETACH, JOIN, TIMEOUT
    };

    struct task {
        void *(*operation) (void *);
        void *params;
        operation_type type;
    };

    typedef struct task task;
private:
    unsigned long avaliableThreads;
    vector<pthread_t> workers;
    queue< task> tasks;                   // task queue

public:
    ThreadPool(unsigned long threads);

    void enqueueTask(task task);

    void notify();

    task getHighPriorityTask();

    bool isAvaliableThread();

    void executeTask(task task);

    void taskFinish(pthread_t pthread);

    void stop();

    bool isTaskActivated();

    void waitForActivatedTasks();

    void printActivatedTasks();
};


#endif //PROJECT2_THREADPOOL_H
