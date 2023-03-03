add_library(builtin_lib
    builtin_cd.c
    builtin_echo.c
    builtin_exit.c
	builtin_continue.c
	builtin_break.c
)

set_target_properties(builtin_lib PROPERTIES
	C_STANDARD 99
	C_EXTENSIONS OFF
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
