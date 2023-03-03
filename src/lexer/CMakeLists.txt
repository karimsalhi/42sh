add_library(lexer_lib
	lexer.c
	create_lexer.c
	create_tab.c
	create_token.c
	free_token.c
	get_type.c
	input_type.c
	peek.c
	pop.c
)

target_include_directories(lexer_lib PUBLIC
	${CMAKE_SOURCE_DIR}/src/utils
	${CMAKE_SOURCE_DIR}/src/parser
)

set_target_properties(lexer_lib PROPERTIES
	C_STANDARD 99
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(lexer_lib PUBLIC
	common_options
	xmalloc_lib
)


