cmake_minimum_required(VERSION 3.16)

project(SharedLibraryTemplateProject)

option(USE_MYLIBRARY_SHARED "Link MyLibrary as shared library" TRUE)

add_subdirectory(mylibrary)

add_executable(Application
    src/main.cpp
)

if(${USE_MYLIBRARY_SHARED})
    target_link_libraries(Application PRIVATE mylibrary)

    if(WIN32)
        add_custom_command(
            TARGET Application POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:mylibrary>
            $<TARGET_FILE_DIR:Application>
        )
    endif()
else()
    target_link_libraries(Application PRIVATE mylibrary-static)
endif()
