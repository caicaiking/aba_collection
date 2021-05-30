//
// Created by 蔡同松 on 2021/5/29.
//

#ifndef ABA_COLLECTION_BLOCKING_QUEUE_H
#define ABA_COLLECTION_BLOCKING_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <cassert>

namespace aba {
    template<typename T>
    class blocking_queue {
    public:
        blocking_queue() = default;
        void put(const T &x) {
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(x);
            this->not_empty_.notify_all();
        }

        void put(T &&x) {
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(std::move(x));
            this->not_empty_.notify_all();
        }

        T take() {
            std::unique_lock<std::mutex> lock(mutex_);

            while (this->queue_.empty()) {
                this->not_empty_.wait(lock);
            }

            assert(!queue_.empty());
            T front(std::move(this->queue_.front()));
            this->queue_.pop();
            return front;
        }

        size_t size() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.size();
        }

    private:
        mutable std::mutex mutex_;
        std::condition_variable not_empty_;
        std::queue<T> queue_;
    };
}

#endif //ABA_COLLECTION_BLOCKING_QUEUE_H
