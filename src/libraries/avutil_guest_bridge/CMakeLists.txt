project(avutil_guest_bridge)

file(GLOB _src *.h *.c *.cpp)
add_library(${PROJECT_NAME} SHARED ${_src})

target_link_libraries(${PROJECT_NAME} PUBLIC avutil_api)
target_link_libraries(${PROJECT_NAME} PRIVATE common)
target_link_libraries(${PROJECT_NAME} PRIVATE qemu-boxed-framework)
target_link_libraries(${PROJECT_NAME} PRIVATE dl)