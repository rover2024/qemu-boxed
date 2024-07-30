project(qemu-boxed-framework LANGUAGES C CXX)

file(GLOB_RECURSE _src *.h *.c *.cpp)
add_library(${PROJECT_NAME} STATIC ${_src})

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} PRIVATE common)