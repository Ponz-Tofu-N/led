cmake_minimum_required(VERSION 3.16)

set(THREADS_PREFER_PTHREAD_FLAG ON)              
set (CMAKE_CXX_STANDARD 14)
project(led)

find_library (BCM2835_LIBRARY NAMES bcm2835)
find_package(Threads REQUIRED)                   

set(SOURCES led_blink.cpp led.cpp)
add_executable(led ${SOURCES})

target_link_libraries (led PUBLIC ${BCM2835_LIBRARY}  "-pthread")
# target_link_libraries(led PUBLIC "-pthread") 
