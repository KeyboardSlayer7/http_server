cmake_minimum_required(VERSION 3.5)
include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/include.zip 
	URL_HASH SHA256=a22461d13119ac5c78f205d3df1db13403e58ce1bb1794edc9313677313f4a9d 
)

FetchContent_MakeAvailable(json)

project(Server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(
    SOURCES
    src/main.cpp
    src/http_parser.h
    src/http_parser.cpp
    src/utils.h
    src/utils.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32)