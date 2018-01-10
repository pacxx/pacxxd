cmake_minimum_required(VERSION 3.5)

project(pacxxd)

find_file(ASIO_HEADER asio.hpp PATHS /usr/include)

if (EXISTS ${ASIO_HEADER})
    message(STATUS "ASIO found")
else()
    message(FATAL_ERROR "ASIO not found")
endif()

set(CMAKE_MODULE_PATH ${PACXX_DIR}/lib/cmake/pacxx)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(PACXX REQUIRED)

include_directories(${PACXX_INCLUDE_DIRECTORY} ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp
                 lib/PACXXHandler.cpp
                 lib/TCPServer.cpp
                 lib/Dispatcher.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wno-attributes)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
add_pacxx_libs_to_target(${PROJECT_NAME})


add_executable(test_client testclient.cpp)
target_link_libraries(test_client Threads::Threads)