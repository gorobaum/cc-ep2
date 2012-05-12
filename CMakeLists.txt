
cmake_minimum_required (VERSION 2.8)

project (ep2 CXX C)
include_directories (src)

set (CMAKE_THREAD_PREFER_PTHREAD True)
find_package (Threads)
if (NOT CMAKE_USE_PTHREADS_INIT)
  message (FATAL_ERROR "Pthread libs not found!")
endif ()

add_executable (ep2
  src/main.cxx
  src/ep2.cxx
  src/barrier.cxx
  src/graph.cxx
  src/log.cxx
  src/multipathseeker.cxx
  src/mutex.cxx
  src/path.cxx
  src/simplepathseeker.cxx
  src/thread.cxx
)

target_link_libraries (ep2 m ${CMAKE_THREAD_LIBS_INIT})
set_target_properties (ep2 PROPERTIES COMPILE_FLAGS "-ansi -Wall -O0 -g")


