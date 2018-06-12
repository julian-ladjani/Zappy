/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_initialisation source file
*/

#include "server_struct.h"

server_user_t *initialise_server_user(int fd)
{
	server_user_t *server_user = malloc(sizeof(server_user_t));

	if (server_user == NULL)
		return (NULL);
	server_user->fd = fd;
	server_user->circular_buffer = circbuf_create(1025);
	if (server_user->circular_buffer == NULL) {
		free(server_user);
		return (NULL);
	}
	server_user->logged_state = ZAPPY_USER_NOT_CONNECTED;
	server_user->nick = NULL;
	server_user->teams = NULL;
	server_user->name = NULL;
	server_user->password = NULL;
	return (server_user);
}