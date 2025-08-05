set(MYLIBRARY_SOURCES
    src/mylibrary.cpp
)

add_library(mylibrary-static
    ${MYLIBRARY_SOURCES}
)

target_include_directories(mylibrary-static PUBLIC include)

add_library(mylibrary SHARED
    ${MYLIBRARY_SOURCES}
)

target_include_directories(mylibrary PUBLIC include)

target_compile_definitions(mylibrary
    PRIVATE BUILD_LIBTYPE_SHARED
    INTERFACE USE_LIBTYPE_SHARED
)
