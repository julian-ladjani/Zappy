cmake_minimum_required(VERSION 3.10)
project(PSU_zappy_2017 C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(CMAKE_C_STANDARD 99)
include_directories(include)


set(CIRCULAR BUFFER
        src/common/circular_buffer/circbuff.c
        src/common/circular_buffer/circbuff_buf.c
        src/common/circular_buffer/circbuff_file.c
        src/common/circular_buffer/circbuff_print.c
        src/common/circular_buffer/circbuff_strings.c
        src/common/circular_buffer/circbuff_utils.c
        include/circbuff.h)

set(CMD_PARSER
        src/common/command_parser/command_parser.c
        include/parser.h)

set(LKN_LIST
        src/common/linked_list/linked_list_add.c
        src/common/linked_list/linked_list_advanced.c
        src/common/linked_list/linked_list_basic.c
        src/common/linked_list/linked_list_conditional.c
        src/common/linked_list/linked_list_create.c
        src/common/linked_list/linked_list_delete.c
        src/common/linked_list/linked_list_get.c
        src/common/linked_list/list_clean.c
        include/linked_list.h)

set(ARG_PARSER
        src/common/arg_parser/arg_parser_cleanup.c
        src/common/arg_parser/arg_parser_initialisation.c
        src/common/arg_parser/argument_regex.c
        src/common/arg_parser/parse_arguments.c
        include/arg_parser.h)

set(COMMAND_PARSER
        circbuff.c
        circbuff_buf.c
        circbuff_file.c
        circbuff_print.c
        circbuff_strings.c
        circbuff_utils.c
        include/circbuff.h)

set(SOCKET
        src/common/socket/socket_initialisation.c
        src/common/socket/socket_cleanup.c
        include/zappy_socket.h)


set(MAP
        src/common/map/map_create.c
        src/common/map/map_free.c
        src/common/map/map_print.c
        src/common/map/map_vector.c
        include/map.h)

set(SERVER
        src/server/main.c
        src/server/server_cleanup.c
        src/server/server_initialisation.c
        src/server/server_loop.c
        src/server/connection/poll_accept.c
        src/server/connection/poll_cleanup.c
        src/server/connection/poll_initialisation.c
        src/server/connection/poll_loop.c
        src/server/team/team_action.c
        src/server/team/team_cleanup.c
        src/server/team/team_initialisation.c
        src/server/team/team_search.c
        src/server/user/user_action.c
        src/server/user/user_cleanup.c
        src/server/user/user_config_check_file.c
        src/server/user/user_get.c
        src/server/user/user_initialisation.c
        src/server/user/user_quit.c
        src/server/user/user_search.c
        include/server_struct.h
        include/server_const.h
        include/server_function.h)

set(CLIENT)

add_executable(server src/ai_client/main.c ${CLIENT} ${LKN_LIST}
        ${CMD_PARSER} ${SOCKET} ${ARG_PARSER}
        ${MAP} ${SERVER})

add_executable(client src/ai_client/main.c ${CLIENT} ${LKN_LIST}
        ${CMD_PARSER} ${SOCKET}
        ${MAP})

target_link_libraries(client -lm)

target_link_libraries(server -lm)
