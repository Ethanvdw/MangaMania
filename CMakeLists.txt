cmake_minimum_required(VERSION 3.22)
project(MangaMania)

set(CMAKE_CXX_STANDARD 23)

# Web requests
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

# JSON parsing
# nlohmann/json

# Image manipulation
# img2pdf

add_executable(MangaMania main.cpp Downloader.cpp Downloader.h Manga.cpp Manga.h UserProgressRecorder.cpp UserProgressRecorder.h)

target_include_directories(MangaMania PRIVATE ${CURL_INCLUDE_DIRS}})
target_link_libraries(MangaMania PRIVATE ${CURL_LIBRARIES})