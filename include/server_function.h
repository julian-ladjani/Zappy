/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_function header file_dir
*/

#ifndef PSU_ZAPPY_2017_SERVER_FUNCTION_H
#define PSU_ZAPPY_2017_SERVER_FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include "server_struct.h"
#include "arg_parser.h"

server_config_t *initialise_server(char *s_port);
server_user_t *initialise_server_user(int fd);
int initialise_socket_poll(server_config_t *server_config);
server_team_t *initialise_server_team(char *name);

void server_main_loop(server_config_t *server_config);
void parse_command(server_config_t *server_config, server_user_t *user);
int poll_loop(server_config_t *server_config);
void poll_accept_client(server_config_t *server_config);

int user_nick_search_criteria(void *user, void *nick);
int user_name_search_criteria(void *user, void *name);
int user_fd_search_criteria(void *user, void *fd);
server_user_t *get_user_by_fd(server_config_t *server_config, int fd);
int team_name_search_criteria(void *team, void *name);
int user_no_team_search_criteria(void *user, void *name);
void team_name_reply(list_t *team, server_user_t *user, char *name);
void user_send_message(server_user_t *user, char *message);
void team_send_message(server_team_t *team, char *message);
void user_send_message_users_same_team(server_config_t *server_config,
	server_user_t *user, char *message);
void team_priv_msg_send_message(server_team_t *team, char *message,
	server_user_t *cur_user);

void cleanup_user_list_elem(void *elem);
void cleanup_server(server_config_t *server_config);
void cleanup_server_exit(server_config_t *server_config,
	unsigned int exit_status);
void cleanup_users(list_t *server_users);
void cleanup_socket_poll(struct pollfd *poll_fd);
void compress_socket_poll(server_config_t *server_config);
void close_socket_poll(server_config_t *server_config, int index);
void cleanup_team_list_elem(void *elem);
void cleanup_teams(list_t *server_teams);

void user_quit(server_config_t *server_config, server_user_t *user,
	char *message);
void user_connect(server_user_t *user);

//arg_parser

arg_parser_output_t *get_arg(arg_parser_input_t *input);
server_argument_t *parse_server_argument(int ac, char **av);
void parse_argument_port(server_argument_t *server_argument,
	arg_parser_input_t *input);

//commands

uint8_t srv_cmd_msz(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_bct(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_mct(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_tna(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_ppo(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_plv(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_pln(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_sgt(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_sst(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_forward(server_config_t *server,
				server_user_t *user, cmdparams_t *cmd);
uint8_t srv_cmd_right(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_left(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_look(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_inventory(server_config_t *server,
				server_user_t *user, cmdparams_t *cmd);
uint8_t srv_cmd_broadcast(server_config_t *server,
				server_user_t *user, cmdparams_t *cmd);
uint8_t srv_cmd_connect_nbr(server_config_t *server,
				server_user_t *user, cmdparams_t *cmd);
uint8_t srv_cmd_fork(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_eject(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_take(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_set(server_config_t *server, server_user_t *user,
			cmdparams_t *cmd);
uint8_t srv_cmd_incantation(server_config_t *server,
				server_user_t *user, cmdparams_t *cmd);

#endif //PSU_ZAPPY_2017_SERVER_FUNCTION_H
