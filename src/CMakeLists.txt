

add_library(parser STATIC parser.c)
add_library(commands STATIC commands.c)
add_library(builtin STATIC builtin.c)

target_link_libraries(commands ${parser})