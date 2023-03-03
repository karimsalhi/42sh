add_library(redirection_lib
	redirection.c
	redirect_output.c
	redirect_input.c
	redirect_append_output.c
	redirect_dup_input.c
	redirect_dup_output.c
	redirect_read_write.c
	redirect_utils.c
)

#target_include_directories(redirection_lib PUBLIC
include_directories(
	${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/src/lexer
    ${CMAKE_SOURCE_DIR}/src/parser
)

set_target_properties(redirection_lib PROPERTIES
	C_STANDARD 99
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(redirection_lib PUBLIC
	common_options
	lexer_lib
	parser_lib
    xmalloc_lib
)
