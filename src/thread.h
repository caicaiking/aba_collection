//
// Created by 蔡同松 on 2021/6/3.
//

#ifndef ABA_COLLECTION_THREAD_H
#define ABA_COLLECTION_THREAD_H
#include "noncopyable.h"
#include <string>
#include <thread>
#include "count_down_latch.h"
#include <functional>
#include <atomic>
namespace  aba
{
    class thread : public noncopyable {
    public:
        using thread_func = std::function<void()>;

        explicit thread(thread_func  fun, const std::string & name = std::string());
        ~thread();
    private:

        void set_default_name();

        std::thread thread_;
        bool started_;
        bool joined_;
        std::thread::id pthread_id;
        thread_func  func_;
        std::string name_;
        count_down_latch latch_;
        static std::atomic_int num_created_;
    };
}



#endif //ABA_COLLECTION_THREAD_H
