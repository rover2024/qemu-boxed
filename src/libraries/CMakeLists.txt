set(_libs avcodec avformat avutil swresample)

foreach(_item IN LISTS _libs)
    add_subdirectory(${_item}_api)
    add_subdirectory(${_item}_guest_bridge)
    add_subdirectory(${_item}_host_bridge)
endforeach()
