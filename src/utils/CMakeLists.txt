add_library(xmalloc_lib
    xmalloc.c
    xmalloc.h
)

set_target_properties(xmalloc_lib PROPERTIES
	C_STANDARD 99
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(xmalloc_lib PRIVATE
	common_options
)
