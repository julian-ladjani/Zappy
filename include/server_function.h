/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_function header file_dir
*/

#ifndef PSU_ZAPPY_2017_SERVER_FUNCTION_H
#define PSU_ZAPPY_2017_SERVER_FUNCTION_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include "server_struct.h"
#include "arg_parser.h"

server_config_t *initialise_server(server_argument_t *server_argument);
server_user_t *initialise_server_user(int fd);
int initialise_socket_poll(server_config_t *server_config);
server_team_t *initialise_server_team(server_config_t *server_config,
	char *name);
list_t *initialise_server_teams(server_config_t *server_config);

void server_main_loop(server_config_t *server_config);
void parse_command(server_config_t *server_config, server_user_t *user);
void exec_pending_command(server_config_t *server_config);
void exec_graphic_command(server_config_t *server_config,
	server_user_t *user, cmdparams_t *cmdparams);
void exec_ai_command(server_config_t *server_config,
	server_user_t *user, cmdparams_t *cmdparams);
int poll_loop(server_config_t *server_config);
void poll_accept_client(server_config_t *server_config);

int user_name_search_criteria(void *user, void *name);
int user_fd_search_criteria(void *user, void *fd);
server_user_t *get_user_by_fd(server_config_t *server_config, int fd);
int team_name_search_criteria(void *team, void *name);
int team_find_nb_user_at_level(server_team_t *team, unsigned int level);
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

void try_to_join_team(server_config_t *server_config,
	server_user_t *user, cmdparams_t *cmdparams);

void send_msg_to_all_graphic(server_config_t *server, char *msg);
void send_player_list_to_user(server_config_t *server,
	server_user_t *graphic);

int find_nb_user_at_pos(server_config_t *server_config,
	ssize_t x, ssize_t y);
int find_nb_user_at_pos_and_level(server_config_t *server_config,
	ssize_t x, ssize_t y, unsigned int level);
server_user_t *find_user_by_id(server_config_t *server, int id);
int get_team_free_slots(server_team_t *team);

uint8_t incantation_end(server_config_t *server, server_user_t *user);
char check_incantation_ressources(server_config_t *server,
	server_user_t *user);
void send_to_player_in_incantation(server_config_t *server,
	server_user_t *user, char *msg);
char check_game_end(server_config_t *server);
void user_action_egg_sup_wait(server_config_t *server, unsigned int nb_tick);
void user_action_sup_wait(server_config_t *server, unsigned int nb_tick);
void close_socket_poll_with_user(server_config_t *server,
	server_user_t *user);
void user_disconect_when_quit_state(server_config_t *server);

//arg_parser

int check_server_arguments(server_argument_t *server_argument);
arg_parser_output_t *get_arg(arg_parser_input_t *input);
server_argument_t *parse_server_argument(int ac, char **av);
void cleanup_server_arguments(server_argument_t *arguments);

void parse_argument_ushort(unsigned short *data, char *start_regexp,
	arg_parser_input_t *input);
void parse_argument_uint(unsigned int *data, char *start_regexp,
	arg_parser_input_t *input);
void parse_argument_size_t(size_t *data, char *start_regexp,
	arg_parser_input_t *input);
void parse_argument_tab(char ***data, char *start_regexp,
	arg_parser_input_t *input);

//timer

void timer_add_mili(struct timespec *timer, unsigned long mili);
unsigned long timer_calc_time_with_frequency(unsigned int frequency,
	unsigned int time_s);
void timer_set_current_time(struct timespec *timer);
int timer_is_ended(struct timespec *timer, struct timespec *cur_time);
void cleanup_timer(struct timespec *timer);
struct timespec *initialise_timer(void);
void timer_sup_mili(struct timespec *timer, unsigned long mili);
unsigned long timer_diff_mili(struct timespec *start,
	struct timespec *end);
unsigned int timer_get_nb_tick(unsigned long mili, unsigned int frequency);
unsigned long timer_get_remain_time_mili(unsigned long mili,
	unsigned int frequency);
unsigned long timer_get_tick_time_mili(unsigned int frequency);
void server_timer_start(server_config_t *server);
void server_timer_end(server_config_t *server);

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
uint8_t srv_cmd_pin(server_config_t *server, server_user_t *user,
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
