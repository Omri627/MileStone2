#include "ThreadPool.h"
#include "ParallelServer.h"
#include <algorithm>
ThreadPool::ThreadPool(unsigned long threads) {
    this->avaliableThreads = threads;
}

void ThreadPool::enqueueTask(task task) {
    this->tasks.emplace(task);
    notify();
}
void ThreadPool::stop() {
    for (pthread_t pthread : this->workers) {
        pthread_cancel(pthread);
    }
}

void ThreadPool::notify() {
    task task;
    pthread_t pthread;
    while (!this->tasks.empty() && this->avaliableThreads > 0) {
        task = this->getHighPriorityTask();
        executeTask(task);
        this->avaliableThreads--;
    }
}

bool ThreadPool::isAvaliableThread() {
    if (this->avaliableThreads > 0)
        return true;
    return false;
}
ThreadPool::task ThreadPool::getHighPriorityTask() {
    task task =  this->tasks.front();
    this->tasks.pop();
    return task;
}

void ThreadPool::executeTask(task task) {
    pthread_t pthread;
    pthread_create(&pthread, nullptr, task.operation, task.params);
    this->workers.push_back(pthread);
    cout << this->workers.size() << endl;
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
    cout << this->workers.size() << endl;
}

void ThreadPool::taskFinish(pthread_t pthread) {
    this->workers.erase(std::remove(this->workers.begin(), this->workers.end(), pthread), this->workers.end());
    this->avaliableThreads++;
    notify();
}
bool ThreadPool::isTaskActivated() {
    cout << "tasks: " << this->workers.size() << endl;
    if (this->workers.size() > 0)
        return true;
    return false;
}
void ThreadPool::waitForActivatedTasks() {
    //todo: discuss the actual time intervals
    const int checkIntervals = 50;
    while (isTaskActivated())
        sleep(checkIntervals);
}
void ThreadPool::printActivatedTasks() {
    cout << "tasks: " << this->workers.size() << endl;
}