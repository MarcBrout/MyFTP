cmake_minimum_required(VERSION 3.6)
project(myftp)

set(CMAKE_C_STANDARD 99)

include_directories(
        /usr/include
        ./include
)

set(MYFTP
        ./include
        ./src/command_cwd.c
        ./src/command_delete.c
        ./src/command_error.c
        ./src/command_help.c
        ./src/command_list.c
        ./src/command_noop.c
        ./src/command_pasv.c
        ./src/command_port.c
        ./src/command_retr.c
        ./src/command_stor.c
        ./src/command_user.c
        ./src/get_command.c
        ./src/raw_command.c
        ./src/server.c
        ./src/server_init.c
        ./src/server_listener.c
        ./src/server_logic.c src/command_quit.c src/command_syst.c)

set(TEST_C
        ./include
        ./src/main_test.c
        ./src/get_command.c)

add_executable(myftp ${MYFTP})

add_executable(test_c ${TEST_C})