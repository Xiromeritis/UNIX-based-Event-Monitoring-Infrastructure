cmake_minimum_required(VERSION 3.10)
project(UnixEventMonitoring C)

set(CMAKE_C_STANDARD 11)

# Build the single-file analyzer executable
add_executable(analyze_log analyze.c)

# Build the multi-threaded analyzer executable
add_executable(parallel_analyze_logs parallel_analyze.c)

# Link the POSIX Threads (pthread) library (Required for parallel execution)
find_package(Threads REQUIRED)
target_link_libraries(parallel_analyze_logs Threads::Threads)