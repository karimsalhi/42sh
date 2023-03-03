find_library(READLINE_LIB readline)

add_executable(42sh main.c)

set_target_properties(42sh PROPERTIES
    C_STANDARD 99
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)


add_subdirectory(utils)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(execution)
add_subdirectory(print_ast)
add_subdirectory(builtin)

target_include_directories(42sh PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/lexer
    ${CMAKE_CURRENT_SOURCE_DIR}/parser
	${CMAKE_CURRENT_SOURCE_DIR}/print_ast
	${CMAKE_CURRENT_SOURCE_DIR}/execution
	${CMAKE_CURRENT_SOURCE_DIR}/builtin
)

target_link_libraries(42sh PRIVATE
	${READLINE_LIB}
	common_options
	lexer_lib
    parser_lib
    xmalloc_lib
	ast_print_lib
	execution_lib
    builtin_lib
)
