#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>

namespace pacxxd{
    class Semaphore {
public:
    Semaphore (int count = 0)
        : _count(count) {}

    inline void signal()
    {
        std::unique_lock<std::mutex> lock(_mtx);
        _count++;
        _cv.notify_all();
    }

    template <typename Duration>
    bool wait_for(const Duration duration)
    {
        std::unique_lock<std::mutex> lock(_mtx);
        auto wait_for_it_success = _cv.wait_for(lock, duration, [this]() { return _count > 0; });
        return wait_for_it_success;
    }

    void reset(){
        std::unique_lock<std::mutex> lock(_mtx);
        _count = 0; 
    }

private:
    std::mutex _mtx;
    std::condition_variable _cv;
    int _count;
};
}