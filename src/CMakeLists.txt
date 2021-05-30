set(Source_files
        main.cpp
        bounded_blocking_queue.h
        )

add_executable(aba_collection ${Source_files})

if(ABA_BUILD_EXAMPLE)
    add_subdirectory(test)
endif()