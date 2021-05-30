//
// Created by 蔡同松 on 2021/5/29.
//

#include "src/count_down_latch.h"
#include <memory>
#include <thread>
#include <iostream>
#include <random>
int rand_within(int value)
{
    std::default_random_engine eng(std::chrono::system_clock::now().time_since_epoch().count());
    return int (eng() /2) % value;
}

void show(std::shared_ptr<aba::count_down_latch> latch)
{
    std::cout << "thread: " << std::this_thread::get_id() <<" start." << std::endl;
    auto sleep_ms = rand_within(1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
    std::cout << "thread: " << std::this_thread::get_id() <<" end." << std::endl;
    latch->count_down();
}

int main()
{
    std::shared_ptr<aba::count_down_latch> latch = std::make_shared<aba::count_down_latch>(5);
    std::cout << "start 5 thread" << std::endl;
    for(int i = 0; i != 5; ++i)
    {
        std::thread(std::bind(show, latch)).detach();
    }

    latch->wait();
    std::cout << "5 threads exited" << std::endl;
}
