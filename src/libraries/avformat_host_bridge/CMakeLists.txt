project(avformat_host_bridge)

file(GLOB _src *.h *.c *.cpp)
add_library(${PROJECT_NAME} SHARED ${_src})

target_link_libraries(${PROJECT_NAME} PUBLIC avformat_api)
target_link_libraries(${PROJECT_NAME} PRIVATE common)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)