add_library(parser_lib
	root.c
    add_child.c
    and_or.c
    command.c
    create_node.c
    element.c
	free_ast.c
    input.c
    list.c
	parser.c
    pipeline.c
    prefix.c
    rule_if.c
    simple_command.c
	shell_command.c
    compound_list.c
    else_clause.c
    do_group.c
    while_rule.c
    until_rule.c
	case_item.c
	case_clause.c
	rule_case.c
    rule_for.c
	funcdec.c
)

add_subdirectory(redirection)

target_include_directories(parser_lib PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../lexer
	${CMAKE_CURRENT_SOURCE_DIR}/../utils
	${CMAKE_CURRENT_SOURCE_DIR}/redirection
)

set_target_properties(parser_lib PROPERTIES
	C_STANDARD 99
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_libraries(parser_lib PUBLIC
	common_options
	lexer_lib
    xmalloc_lib
	redirection_lib
)
