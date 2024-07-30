get_filename_component(CURRENT_LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_subdirectory(api)
add_subdirectory(guest_bridge)
add_subdirectory(host_bridge)