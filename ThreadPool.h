//
// Created by ranraboh on 12/01/19.
//

#ifndef PROJECT2_THREADPOOL_H
#define PROJECT2_THREADPOOL_H

#include <functional>
#include <queue>
#include "pthread.h"
using namespace std;
/**
 *  manage tasks and thread in application.
 *  the objective of thread pool
 *  is to make multi-tasking applications easier to write and more flexible.
 */
class ThreadPool {
public:
    /**
     * indicate type of execution of pthread worker
     * detach: pthread execution is independent to other running pthreads.
     * join: the activating pthread joined to new created pthread and resumed after the termination of it.
     * timeout: activate pthread for fixed amount of time.
     */
    enum operation_type {
        DETACH, JOIN, TIMEOUT
    };
    /**
     * tasks are chunk of code or functions in application.
     */
    struct task {
        void *(*operation) (void *);
        void *params;
        operation_type type;
    };
    typedef struct task task;
private:
    /* number of avaliable workers i.e threads in application */
    unsigned long avaliableThreads;
    /* data structure holding the busy workers. threads which presently execute tasks in application */
    vector<pthread_t> workers;
    /* queue structure of chunks of code or functions that should be execute */
    queue< task> tasks;

public:
    /**
     * the constructor gets number of workers (parallel threads)
     * and creates thread pool object which manage the tasks and threads.
     * which make multi-tasking applications easier to write and more flexible.
     * @param threads
     */
    ThreadPool(unsigned long threads);
    /**
     * enqueueTask method gets single task that should be perform in multi-threading environment.
     * the method insert the task into queue.
     * the method executes the task if there enough availiable resources
     * @param task
     */
    void enqueueTask(task task);
    /**
     * notify is called whenever there is any update in thread pool.
     * that means if a thread execution completed or a new task enqueued
     * the method linked between avaliable threads and tasks.
     */
    void notify();
    /**
     * getHighPriorityTask method return the higest prioirty task stored in queue.
     * @return highest priority task.
     */
    task getHighPriorityTask();
    /**
     * isAvaliableThread method indicate whether there is avaliable threads (=workers)
     * in application.
     * @return returns true if there is avaliable threads.
     * at any other case returns false.
     */
    bool isAvaliableThread();
    /**
     * executeTask method gets a specific task.
     * the method looks for resources to execute the task.
     * @param task specific task in application
     */
    void executeTask(task task);
    /**
     * taskFinish method called whenever a pthread finished his task.
     * the method updates the object inner data.
     * @param pthread
     */
    void taskFinish(pthread_t pthread);
    /**
     * stop method called for a termination of tasks in application
     */
    void stop();
    /**
     * isTaskActivated method checks if there any activated tasks in application
     * at that moment.
     * @return returns true if and only if there is activated task.
     */
    bool isTaskActivated();
    /**
     * wait for activated tasks in application and resume after their termination
     */
    void waitForActivatedTasks();

    void printActivatedTasks();
};


#endif //PROJECT2_THREADPOOL_H
