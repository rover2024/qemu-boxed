project(prog LANGUAGES C)

file(GLOB _src *.h *.hpp *.c)
add_executable(${PROJECT_NAME} ${_src})

target_link_libraries(${PROJECT_NAME} PRIVATE
    avcodec_guest_bridge
    avdevice_guest_bridge
    avfilter_guest_bridge
    avformat_guest_bridge
    avutil_guest_bridge
    swresample_guest_bridge
    swscale_guest_bridge
)