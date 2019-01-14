#include "ThreadPool.h"
#include "ParallelServer.h"
#include <algorithm>
/**
 * the constructor gets number of workers (parallel threads)
 * and creates thread pool object which manage the tasks and threads.
 * which make multi-tasking applications easier to write and more flexible.
 * @param threads
 */
ThreadPool::ThreadPool(unsigned long threads) {
    this->avaliableThreads = threads;
}
/**
 * notify is called whenever there is any update in thread pool.
 * that means if a thread execution completed or a new task enqueued
 * the method linked between avaliable threads and tasks.
 */
void ThreadPool::enqueueTask(task task) {
    this->tasks.emplace(task);
    notify();
}
/**
 * stop method called for a termination of tasks in application
 */
void ThreadPool::stop() {
    for (pthread_t pthread : this->workers) {
        pthread_cancel(pthread);
    }
}
/**
 * notify is called whenever there is any update in thread pool.
 * that means if a thread execution completed or a new task enqueued
 * the method linked between avaliable threads and tasks.
 */
void ThreadPool::notify() {
    task task;
    pthread_t pthread;
    while (!this->tasks.empty() && this->avaliableThreads > 0) {
        task = this->getHighPriorityTask();
        executeTask(task);
        this->avaliableThreads--;
    }
}
/**
 * isAvaliableThread method indicate whether there is avaliable threads (=workers)
 * in application.
 * @return returns true if there is avaliable threads.
 * at any other case returns false.
 */
bool ThreadPool::isAvaliableThread() {
    if (this->avaliableThreads > 0)
        return true;
    return false;
}
/**
 * getHighPriorityTask method return the higest prioirty task stored in queue.
 * @return highest priority task.
 */
ThreadPool::task ThreadPool::getHighPriorityTask() {
    task task =  this->tasks.front();
    this->tasks.pop();
    return task;
}
/**
 * executeTask method gets a specific task.
 * the method looks for resources to execute the task.
 * @param task specific task in application
 */
void ThreadPool::executeTask(task task) {
    pthread_t pthread;
    pthread_create(&pthread, nullptr, task.operation, task.params);
    this->workers.push_back(pthread);
    switch (task.type) {
        case DETACH: pthread_detach(pthread);
            break;
        case JOIN: pthread_join(pthread, nullptr);
            this->taskFinish(pthread);
            break;
        case TIMEOUT:
            /* set timer for thread */
            struct timespec abstime;                      // timer object
            clock_gettime(CLOCK_REALTIME, &abstime);
            abstime.tv_sec += 10;
            pthread_timedjoin_np(pthread, nullptr, &abstime);
            this->taskFinish(pthread);
    }
}
/**
 * taskFinish method called whenever a pthread finished his task.
 * the method updates the object inner data.
 * @param pthread
 */
void ThreadPool::taskFinish(pthread_t pthread) {
    this->workers.erase(std::remove(this->workers.begin(), this->workers.end(), pthread), this->workers.end());
    this->avaliableThreads++;
    notify();
}
/**
 * isTaskActivated method checks if there any activated tasks in application
 * at that moment.
 * @return returns true if and only if there is activated task.
 */
bool ThreadPool::isTaskActivated() {
    if (this->workers.size() > 0)
        return true;
    return false;
}
/**
 * wait for activated tasks in application and resume after their termination
 */
void ThreadPool::waitForActivatedTasks() {
    //todo: discuss the actual time intervals
    const int checkIntervals = 20;
    while (isTaskActivated())
        sleep(checkIntervals);
}
void ThreadPool::printActivatedTasks() {
    cout << "tasks: " << this->workers.size() << endl;
}