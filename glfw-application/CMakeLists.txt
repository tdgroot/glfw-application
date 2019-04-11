find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)

include_directories(src src/tests ${OPENGL_INCLUDE_DIR} vendor)

file(GLOB SOURCES src/*.cpp)
file(GLOB TEST_SOURCES src/tests/*.cpp)
file(GLOB IMGUI_SOURCES vendor/imgui/*.cpp)

add_executable(glfw_application
        src/glfw-application.cpp
        src/glad.c
        ${SOURCES}
        ${TEST_SOURCES}
        ${IMGUI_SOURCES}
)

target_link_libraries(glfw_application
        glfw
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY}
        ${Boost_LIBRARIES}
)

if (UNIX)
    # Need to link libdl on Linux:
    # - https://github.com/Dav1dde/glad/issues/78#issuecomment-277487098
    # - https://cmake.org/cmake/help/v3.0/variable/CMAKE_DL_LIBS.html
    target_link_libraries(glfw_application ${CMAKE_DL_LIBS})
endif()
