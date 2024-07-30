project(prog)

file(GLOB _src *.h *.hpp *.c *.cpp)
add_executable(${PROJECT_NAME} ${_src})

target_link_libraries(${PROJECT_NAME} PRIVATE
    avcodec_guest_bridge
    avformat_guest_bridge
    avutil_guest_bridge
    swresample_guest_bridge
)