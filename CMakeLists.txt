cmake_minimum_required(VERSION 3.8)
project(42sh VERSION 1.0.0 LANGUAGES C)

add_library(common_options INTERFACE)

target_compile_options(common_options INTERFACE
	"-Wall"
	"-Wextra"
	"-Werror"
	"-pedantic"
	"-fsanitize=address"
	"-D_POSIX_C_SOURCE=200809L"
	"-g"
)

target_link_libraries(common_options INTERFACE
	$<$<NOT:$<CONFIG:Release>>:-fsanitize=address>
)

add_subdirectory(src)
add_subdirectory(doc)

find_library(CRITERION_LIB criterion)
if (CRITERION_LIB)
    add_subdirectory(tests)
    enable_testing()
    add_test(NAME testsuite COMMAND testsuite)
endif()
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose DEPENDS testsuite)
