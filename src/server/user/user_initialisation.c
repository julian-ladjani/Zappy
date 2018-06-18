/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_initialisation source file
*/

#include "server_struct.h"

server_user_t *initialise_server_user(int fd)
{
	server_user_t *server_user = calloc(sizeof(server_user_t),
		sizeof(server_user_t));

	if (server_user == NULL)
		return (NULL);
	server_user->fd = fd;
	server_user->circular_buffer = circbuf_create(1025);
	if (server_user->circular_buffer == NULL) {
		free(server_user);
		return (NULL);
	}
	server_user->logged_state = ZAPPY_USER_NOT_CONNECTED;
	server_user->orientation = (cardinal_dir_t) rand() % 4 + 1;
	server_user->level = 1;
	server_user->type = ZAPPY_USER_NO_TYPE;
	return (server_user);
}
