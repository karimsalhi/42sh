#find_package(PkgConfig)

#find_path(CRITERION_INCLUDE_DIR criterion/criterion.h
	#PATH_SUFFIXES criterion
	#)

	find_library(CRITERION_LIB criterion)

#set(CRITERION_LIBRAIRIES ${CRITERION_LIBRARY})
#set(CRITERION_INCLUDE_DIRS ${CRITERION_INCLUDE_DIR})

add_executable(testsuite
    test_get_type.c
    test_get_token.c
    #test_parser_if.c tu pourras le decommenter quand t auras implementer le fonction freetab
    #test_parser_prefix.c IDEM
    test_echo_builtin.c
	test_variable.c
	test_variable_substitution.c
)

set_target_properties(testsuite PROPERTIES
	C_STANDARD 99
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(testsuite PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/lexer
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/execution
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/builtin
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/parser/redirection
)

target_link_libraries(testsuite PRIVATE
	${CRITERION_LIB}
	common_options
    lexer_lib
	parser_lib
    builtin_lib
	redirection_lib
	execution_lib
)

set_target_properties(testsuite PROPERTIES EXCLUDE_FROM_ALL TRUE)
