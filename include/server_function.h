/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** 	server_function header file_dir
*/

#ifndef PSU_MYIRC_2017_SERVER_FUNCTION_H
#define PSU_MYIRC_2017_SERVER_FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include "server_struct.h"

server_config_t *initialise_server(char *s_port);
server_user_t *initialise_server_user(int fd);
zappy_socket_t *initialise_socket(int port);
int initialise_socket_poll(server_config_t *server_config);
server_channel_t *initialise_server_channel(char *name);

void server_main_loop(server_config_t *server_config);
char *read_line(int fd);
void parse_command(server_config_t *server_config, server_user_t *user);
int poll_loop(server_config_t *server_config);
void poll_accept_client(server_config_t *server_config);

list_t *list_files_and_folders_at_path(char *path);
list_t *list_files_at_path(char *path);
void delete_file_list_elem(void *elem);
FILE *open_filename_path(char *path, char *filename, char *rights);
char *get_filename_path(char *path, char *filename);
list_t *check_user_file_list(list_t *file_list);
int path_is_dir(char *path);
int path_exist(char *path);
char *get_command_str(server_user_t *server_user);
command_t *tokenize_command(char *command_str);
int user_nick_search_criteria(void *user, void *nick);
int user_name_search_criteria(void *user, void *name);
int user_fd_search_criteria(void *user, void *fd);
server_user_t *get_user_by_fd(server_config_t *server_config, int fd);
int channel_name_search_criteria(void *channel, void *name);
int user_no_channel_search_criteria(void *user, void *name);
void channel_name_reply(list_t *channel, server_user_t *user, char *name);
void user_send_message(server_user_t *user, char *message);
void channel_send_message(server_channel_t *channel, char *message);
void user_send_message_users_same_channel(server_config_t *server_config,
	server_user_t *user, char *message);
void channel_priv_msg_send_message(server_channel_t *channel, char *message,
	server_user_t *cur_user);

void cleanup_user_list_elem(void *elem);
void cleanup_server(server_config_t *server_config);
void cleanup_server_exit(server_config_t *server_config,
	unsigned int exit_status);
void cleanup_users(list_t *server_users);
void cleanup_socket(zappy_socket_t *master);
void cleanup_socket_poll(struct pollfd *poll_fd);
void compress_socket_poll(server_config_t *server_config);
void close_socket_poll(server_config_t *server_config, int index);
void cleanup_command(command_t *command);
void cleanup_channel_list_elem(void *elem);
void cleanup_channels(list_t *server_channels);

void fill_command_arg(char **args, char *command_arg);
int check_user_pass(server_user_t *user, char *password);
void read_write(int from_fd, int to_fd);
void user_quit(server_config_t *server_config, server_user_t *user,
	char *message);
void user_connect(server_user_t *user);

void irc_command_nick(server_config_t *server_config, server_user_t *user,
	command_t *command);
void irc_command_user(server_config_t *server_config, server_user_t *user,
	command_t *command);
void irc_command_users(server_config_t *server_config,
	server_user_t *user, command_t *command);
void irc_command_names(server_config_t *server_config,
	server_user_t *user, command_t *command);
void irc_command_join(server_config_t *server_config,
	server_user_t *user, command_t *command);
void irc_command_privmsg(server_config_t *server_config,
	server_user_t *user, command_t *command);
void irc_command_part(server_config_t *server_config,
	server_user_t *user, command_t *command);
void irc_command_quit(server_config_t *server_config,
	server_user_t *user, command_t *command);
void irc_command_list(server_config_t *server_config,
	server_user_t *user, command_t *command);
void irc_command_privmsg_channel(server_config_t *server_config,
	server_user_t *user, char *name, char *message);
void irc_command_privmsg_user(server_config_t *server_config,
	server_user_t *user, char *name, char *message);

#endif //PSU_MYIRC_2017_SERVER_FUNCTION_H
