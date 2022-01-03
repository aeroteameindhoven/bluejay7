#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <queue>
#include "task.h"
#include <ros/ros.h>

#define MAX_THREADS std::thread::hardware_concurrency() - 1;

class thread_pool
{
public:
    //disable copy and assign a thread pool
    thread_pool(const thread_pool&) = delete;
    thread_pool &operator=(const thread_pool&) = delete;

    void threadManager [[noreturn]]() {
        ROS_INFO("new worker thread created");
        while (true) {
            std::unique_lock<std::mutex> lock(jobMutex);
            newJob.wait(lock, [this] {return !jobQueue.empty(); });
            lock.unlock();
            Task a = (jobQueue.front());
            jobQueue.pop();
            activeTask.push_back(a.getID());
            a.executeTask();
        }
    }

    std::vector<int> getActiveTask(){
        return activeTask;
    }

    ~thread_pool(){
        if (!Pool.empty()){
            for (auto& thread : Pool) {
                thread.join();
            }
        }
    }

    thread_pool(uint8_t _numThreads) : numThreads(_numThreads) {
        unsigned int tmp = MAX_THREADS;
        ROS_INFO("Hardware can support: %d", tmp);
        if(tmp == 0){
            numThreads = 1;
        } else if(numThreads > tmp){
            numThreads = static_cast<uint8_t>(tmp);
        }
        Pool.reserve(numThreads);
        for(int i = 0; i != numThreads; ++i){
            Pool.emplace_back(std::thread(&thread_pool::threadManager, this));
        }
    }

    void submit (Task newTask) {
        std::unique_lock<std::mutex> lock(jobMutex);
        jobQueue.emplace(newTask);
        newJob.notify_one();
    }
private:
    uint8_t numThreads; // number of threads in the pool
    std::vector<std::thread> Pool; //the actual thread pool
    std::queue<Task> jobQueue;
    std::vector<int> activeTask;
    std::condition_variable newJob;// used to notify threads about available jobs
    std::mutex jobMutex; // used to push/pop jobs to/from the queue
};

#endif // THREADPOOL_H

