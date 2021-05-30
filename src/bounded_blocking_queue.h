//
// Created by 蔡同松 on 2021/5/30.
//

#ifndef ABA_COLLECTION_BOUNDED_BLOCKING_QUEUE_H
#define ABA_COLLECTION_BOUNDED_BLOCKING_QUEUE_H

#include <boost/circular_buffer.hpp>
#include <mutex>
#include <condition_variable>

namespace aba {
    template <typename T>
    class bounded_blocking_queue {
    public:

        explicit bounded_blocking_queue(int max_size) :
                queue_(max_size) {}

        void put(const T &x) {
            std::unique_lock<std::mutex> lock(this->mutex_);

            while (this->queue_.full()) {
                this->not_full_.wait(lock);
            }

            assert(!this->queue_.full());
            this->queue_.push_back(x);
            this->not_empty_.notify_all();
        }

        void put(T &&x) {
            std::unique_lock<std::mutex> lock(this->mutex_);

            while (this->queue_.full()) {
                this->not_full_.wait(lock);
            }

            assert(!this->queue_.full());
            this->queue_.push_back(std::move(x));
            this->not_empty_.notify_all();
        }


        T take() {
            std::unique_lock<std::mutex> lock(this->mutex_);

            while (this->queue_.empty()) {
                this->not_empty_.wait(lock);
            }

            assert(!this->queue_.empty());

            T front(std::move(this->queue_.front()));
            this->queue_.pop_front();
            this->not_full_.notify_all();
            return front;
        }

        bool empty() const {
            std::lock_guard<std::mutex> lock(this->mutex_);
            return this->queue_.empty();
        }

        bool full() const {
            std::lock_guard<std::mutex> lock(this->mutex_);
            return this->queue_.full();
        }


        size_t size() const {
            std::lock_guard<std::mutex> lock(this->mutex_);
            return this->queue_.size();
        }

        size_t capacity() const {
            std::lock_guard<std::mutex> lock(this->mutex_);
            return this->queue_.capacity();
        }

    private:
        mutable std::mutex mutex_;
        std::condition_variable not_empty_;
        std::condition_variable not_full_;
        boost::circular_buffer<T> queue_;
    };
}
#endif //ABA_COLLECTION_BOUNDED_BLOCKING_QUEUE_H
