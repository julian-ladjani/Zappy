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
	server_users->circular_buffer->free(server_users->circular_buffer);
	server_users->team = NULL;
	free(elem);
}

void cleanup_users(list_t *server_users)
{
	printf("Info: Cleanup Users\n");
	if (server_users == NULL)
		return;
	list_delete_all(server_users, cleanup_user_list_elem);
}