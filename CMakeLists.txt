cmake_minimum_required(VERSION 3.14)
project(spatial_implementation)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# BOOST
# RUN brew install boost in your terminal and configure the destination files
set(Boost_INCLUDE_DIR /usr/local/Cellar/boost/1.76.0/include)
set(Boost_LIBRARY_DIR /usr/local/Cellar/boost/1.76.0/lib)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

FetchContent_MakeAvailable(
  googletest)

enable_testing()

add_executable(
  quad_test
  quad_test.cpp
)

target_link_libraries(
  quad_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(quad_test)