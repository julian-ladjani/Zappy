/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_cleanup source file_dir
*/

#include <unistd.h>
#include <stdio.h>
#include "server_struct.h"

void cleanup_user_list_elem(void *elem)
{
	server_user_t *server_users = elem;

	if (elem == NULL)
		return;
	free(server_users->nick);
	free(server_users->name);
	free(server_users->password);
	server_users->circular_buffer->free(server_users->circular_buffer);
	list_delete_all(server_users->teams, NULL);
	free(elem);
}

void cleanup_users(list_t *server_users)
{
	printf("Info: Cleanup Users\n");
	if (server_users == NULL)
		return;
	list_delete_all(server_users, cleanup_user_list_elem);
}