//
// Created by 蔡同松 on 2021/6/3.
//

#include "thread.h"
#include <unistd.h>
#include <stdlib.h>

using namespace  aba;

namespace  detail
{

}

thread::thread(thread_func fun, const std::string &name): latch_(1) {

}
