CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

project(aba_collection C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)


enable_testing()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_PROJECT_NAME STREQUAL "aba_collection")
    option(ABA_BUILD_EXAMPLE "Build aba_collection examples" ON)
endif()

include_directories(${PROJECT_SOURCE_DIR})
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

add_subdirectory(src)



