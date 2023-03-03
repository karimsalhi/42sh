add_library(ast_print_lib
	print_ast.h
	print_ast.c
)

set_target_properties(ast_print_lib PROPERTIES
	C_STANDARD 99
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(ast_print_lib PUBLIC
	${CMAKE_SOURCE_DIR}/src/utils
	${CMAKE_SOURCE_DIR}/src/parser
)

target_link_libraries(ast_print_lib PUBLIC
	common_options
	xmalloc_lib
)
