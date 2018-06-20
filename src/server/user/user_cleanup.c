/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_cleanup source file_dir
*/

#include <unistd.h>
#include <stdio.h>
#include "server_struct.h"
#include "server_function.h"

void cleanup_user_list_elem(void *elem)
{
	server_user_t *server_user = elem;

	if (elem == NULL)
		return;
	server_user->circular_buffer->free(server_user->circular_buffer);
	if (server_user->team)
		list_delete_elem(list_get_elem_with_content(
			server_user->team->users, server_user), NULL);
	server_user->commands = list_delete_all(server_user->commands,
						&free_arguments);
	server_user->team = NULL;
	cleanup_user_timer(server_user->wait);
	free(elem);
}

void cleanup_users(list_t *server_users)
{
	printf("Info: Cleanup Users\n");
	if (server_users == NULL)
		return;
	list_delete_all(server_users, cleanup_user_list_elem);
}
