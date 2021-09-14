cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME gui_application_cube_demo)
project( ${PROJECT_NAME} )

include("compiler_options.cmake")

add_executable(
    ${PROJECT_NAME}  
    src/cube_demo.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME} PUBLIC gui_application)
target_link_libraries(${PROJECT_NAME} PUBLIC simple_draw_gl)

