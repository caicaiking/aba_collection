//
// Created by 蔡同松 on 2021/5/29.
//

#include "src/bounded_blocking_queue.h"
#include "src/count_down_latch.h"
#include <thread>
#include <vector>
#include <chrono>
#include <zconf.h>

class test
{
public:
    explicit  test(int num_thread):queue_(20), latch_(num_thread)
    {
        for(int i = 0; i != num_thread; ++i)
        {
            auto t = std::make_unique<std::thread>(
                    [this] { thread_fun(); }
                    );
            this->threads_.emplace_back(std::move(t));
        }
    }

    void run(int times)
    {
        printf("waiting for count down latch\n");
        latch_.wait();

        printf("all threads started\n");

        for(int i = 0; i != times; ++i)
        {
            char buf[32]={0};
            snprintf(buf, sizeof buf, "hello %d", i);
            queue_.put(buf);
            printf("tid=%d, put data = %s, size = %zd\n", std::this_thread::get_id(), buf, queue_.size());
        }
    }

    void join_all()
    {
        for(size_t i = 0; i != threads_.size(); ++i)
        {
            queue_.put("stop");
        }

        for(auto & item: this->threads_)
        {
            item->join();
        }
    }

private:
    void thread_fun()
    {
        printf("tid: %d, started \n", std::this_thread::get_id());
        latch_.count_down();

        bool running = true;
        while(running)
        {
            std::string d(queue_.take());
            printf("tid: %d, get data= %s, size = %zd\n", std::this_thread::get_id(), d.c_str(), queue_.size());

            using namespace std::chrono_literals;
            std::this_thread::sleep_for(1ms);
            running  = (d != "stop");
        }

        printf("tid = %d stopped\n", std::this_thread::get_id());
    }

private:
    aba::bounded_blocking_queue<std::string> queue_;
    aba::count_down_latch latch_;
    std::vector<std::unique_ptr<std::thread>> threads_;
};


int main(int argc, char** argv)
{

    printf("pid=%d, tid = %d", ::getpid(), std::this_thread::get_id());
    test t(5);

    t.run(100);
    t.join_all();

    return 0;
}
