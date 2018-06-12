cmake_minimum_required(VERSION 3.10)
project(PSU_zappy_2017 C)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set(CMAKE_C_STANDARD 99)

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
        src/common/arg_parser/arg_parser_initalisation.c
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

set(MAP
        src/common/map/create_map.c
        src/common/map/free_map.c
        src/common/map/print_map.c
        include/map.h)

set(CLIENT)

add_executable(client src/ai_client/main.c ${CLIENT} ${COMMON} ${CMD_PARSER}
        ${MAP})
