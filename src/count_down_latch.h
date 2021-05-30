//
// Created by 蔡同松 on 2021/5/29.
//

#ifndef ABA_COLLECTION_COUNT_DOWN_LATCH_H
#define ABA_COLLECTION_COUNT_DOWN_LATCH_H

#include <mutex>
#include <condition_variable>
#include "noncopyable.h"


namespace aba {
    class count_down_latch : public noncopyable {
    public:
        explicit count_down_latch(int count) : count_(count) {}

        void wait() {
            std::unique_lock<std::mutex> lock(this->mutex_);
            while (count_ > 0) {
                this->cond_.wait(lock);
            }
        }

        void count_down() {
            std::lock_guard<std::mutex> lock(this->mutex_);
            --count_;

            if (count_ == 0) {
                this->cond_.notify_all();
            }
        }

    private:
        int count_;
        mutable std::mutex mutex_;
        std::condition_variable cond_;
    };
}

#endif //ABA_COLLECTION_COUNT_DOWN_LATCH_H
