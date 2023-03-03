add_library(execution_lib
	exec_root.c
	exec_cmd.c
	exec_and_or.c
	exec_compound_list.c
	exec_command.c
	exec_funcdec.c
	exec_input.c
	exec_list.c
	exec_pipeline.c
	exec_redirection.c
	exec_rule_if.c
	exec_shell_command.c
	exec_simple_command.c
	exec_else_clause.c
	exec_redirect.c
	exec_redirect_input.c
	exec_redirect_append_output.c
	exec_redirect_dup_input.c
	exec_redirect_dup_output.c
	exec_redirect_rdwr.c
	exec_rule_while.c
	exec_rule_until.c
	exec_do_group.c
	exec_value.c
	exec_variable_substitution.c
	exec_quoting.c
	exec_assignement_word.c
	exec_substitution_cmd.c
	exec_rule_for.c
	exec_case.c
)


set_target_properties(execution_lib PROPERTIES
	C_STANDARD 99
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(execution_lib PUBLIC
	${CMAKE_SOURCE_DIR}/src/utils
	${CMAKE_SOURCE_DIR}/src/parser
	${CMAKE_SOURCE_DIR}/src/lexer
	${CMAKE_SOURCE_DIR}/src/builtin
)

target_link_libraries(execution_lib PUBLIC
	common_options
	lexer_lib
    xmalloc_lib
	parser_lib
	lexer_lib
	builtin_lib
)
