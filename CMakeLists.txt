cmake_minimum_required(VERSION 3.15)
project(NetworkApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_library(net STATIC src/net/Socket.cpp src/net/TcpClient.cpp src/net/TcpServer.cpp)
target_include_directories(net PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/net)

add_library(processing STATIC src/processing/TextProcessor.cpp)
target_include_directories(processing PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/processing)

add_executable(console_client src/console_client/main.cpp)
target_link_libraries(console_client PRIVATE net processing)

add_executable(processing_server src/processing_server/main.cpp)
target_link_libraries(processing_server PRIVATE net processing)

add_executable(display_server src/display_server/main.cpp)
target_link_libraries(display_server PRIVATE net)

find_package(GTest CONFIG REQUIRED)

add_executable(tests tests/TextProcessor_test.cpp tests/Socket_test.cpp tests/TcpClient_test.cpp tests/TcpServer_test.cpp)
target_link_libraries(tests PRIVATE net processing GTest::gtest GTest::gtest_main)