project(avutil_api)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${PROJECT_NAME} INTERFACE "/home/overworld/Documents/GitHub/ffmpeg-audio-convert/vcpkg/installed/x64-linux/include/ffmpeg-fake")