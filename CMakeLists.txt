cmake_minimum_required(VERSION 3.10)
project(PSU_zappy_2017 C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set( CMAKE_CXX_FLAGS "-Wall -Werror -Wextra " )
set(CMAKE_C_STANDARD 99)
include_directories(include)


set(CIRCULAR_BUFFER
        src/common/circular_buffer/circbuff.c
        src/common/circular_buffer/circbuff_buf.c
        src/common/circular_buffer/circbuff_file.c
        src/common/circular_buffer/circbuff_print.c
        src/common/circular_buffer/circbuff_strings.c
        src/common/circular_buffer/circbuff_utils.c
        include/circbuff.h)

set(CMD_PARSER
        src/common/command_parser/command_parser.c
        src/common/command_parser/my_strtok.c
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
        src/common/arg_parser/parsing_functions/arg_parser_string.c
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
        src/common/map/map_orientation.c
        src/common/map/map_print.c
        src/common/map/map_vector.c
        src/common/map/map_str_to_tile.c
        src/common/map/map_tile_to_str.c
        src/common/map/map_debug.c
        include/map.h)

set(UTILS
        src/common/utils/str_append.c
        src/common/utils/tab_cpy.c
        include/utils.h
        include/ressources_str.h
        src/common/utils/epurstr.c)

set(SERVER
        src/server/commands/ai_commands/broadcast.c
        src/server/commands/ai_commands/connect_nbr.c
        src/server/commands/ai_commands/eject.c
        src/server/commands/ai_commands/fork.c
        src/server/commands/ai_commands/forward.c
        src/server/commands/ai_commands/incantation.c
        src/server/commands/ai_commands/inventory.c
        src/server/commands/ai_commands/left.c
        src/server/commands/ai_commands/look.c
        src/server/commands/ai_commands/right.c
        src/server/commands/ai_commands/set.c
        src/server/commands/ai_commands/take.c
        src/server/commands/ai_command_exec.c
        src/server/commands/graphic_commands/bct.c
        src/server/commands/graphic_commands/mct.c
        src/server/commands/graphic_commands/msz.c
        src/server/commands/graphic_commands/pin.c
        src/server/commands/graphic_commands/plv.c
        src/server/commands/graphic_commands/ppo.c
        src/server/commands/graphic_commands/sgt.c
        src/server/commands/graphic_commands/sst.c
        src/server/commands/graphic_commands/tna.c
        src/server/commands/graphic_command_exec.c
        src/server/send_messages.c
        src/server/server_cleanup.c
        src/server/server_initialisation.c
        src/server/server_loop.c
        src/server/connection/poll_accept.c
        src/server/connection/poll_cleanup.c
        src/server/connection/poll_initialisation.c
        src/server/connection/poll_loop.c
        src/server/team/team_cleanup.c
        src/server/team/team_initialisation.c
        src/server/team/team_search.c
        src/server/user/user_action.c
        src/server/user/user_cleanup.c
        src/server/user/user_get.c
        src/server/user/user_initialisation.c
        src/server/user/user_quit.c
        src/server/user/user_search.c
        include/server_struct.h
        include/server_const.h
        include/server_function.h
        src/server/commands/command_exec.c
        src/server/commands/command_parse.c
        src/server/commands/ai_command_exec.c
        src/server/commands/graphic_command_exec.c
        src/server/commands/join_team.c
        src/server/argument/server_parse_arg.c
        src/server/argument/server_parse_arg_func.c
        src/server/argument/cleanup_server_arguments.c
        src/server/argument/server_check_arg.c
        src/server/timer/timer_initialisation.c
        src/server/timer/timer_cleanup.c
        src/server/timer/timer_action.c src/server/timer/timer_check.c)

set(CLIENT
        include/client.h
        include/client_sender.h
        src/ai_client/commands/send/broadcast.c
        src/ai_client/commands/send/connect_nbr.c
        src/ai_client/commands/send/eject.c
        src/ai_client/commands/send/fork.c
        src/ai_client/commands/send/forward.c
        src/ai_client/commands/send/incantation.c
        src/ai_client/commands/send/inventory.c
        src/ai_client/commands/send/left.c
        src/ai_client/commands/send/look.c
        src/ai_client/commands/send/right.c
        src/ai_client/commands/send/set.c
        src/ai_client/commands/send/take.c
        src/ai_client/help.c
        src/ai_client/connect.c
        src/ai_client/launch_server.c
        src/ai_client/commands/sender.c
        src/ai_client/commands/sender.c
        include/client_connection.h
        src/ai_client/commands/pre_requests.c
        src/common/utils/is_str.c
        src/ai_client/parser.c
        include/client_parser.h
        src/ai_client/ai/launch_ai.c
        include/map_debug.h
        src/ai_client/commands/srv_requests.c
        include/ai_modes.h
        src/ai_client/ai/searcher.c
        src/ai_client/ai/shouter.c
        src/ai_client/ai/follower.c
        src/ai_client/ai/conditions.c
        src/ai_client/commands/send/incantation_wait.c)

add_executable(zappy_server src/server/main.c ${SERVER} ${LKN_LIST}
        ${CMD_PARSER} ${SOCKET} ${UTILS} ${ARG_PARSER} ${MAP}
        ${CIRCULAR_BUFFER})

add_executable(zappy_ai src/ai_client/main.c ${CLIENT} ${LKN_LIST}
        ${CMD_PARSER} ${SOCKET} ${UTILS} ${ARG_PARSER} ${MAP}
        ${CIRCULAR_BUFFER})

target_link_libraries(zappy_ai -lm -lpthread)

target_link_libraries(zappy_server -lm)
