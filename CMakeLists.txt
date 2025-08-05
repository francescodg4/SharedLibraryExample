cmake_minimum_required(VERSION 3.16)

project(SharedLibraryTemplateProject)

add_subdirectory(mylibrary/)

add_executable(Application
    src/main.cpp
)

target_link_libraries(Application PRIVATE mylibrary)
