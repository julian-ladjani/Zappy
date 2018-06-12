/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	socket_cleanup source file
*/

#include <stdio.h>
#include <sys/socket.h>
#include "zappy_socket.h"
#include "server_struct.h"

void cleanup_socket(zappy_socket_t *master)
{
	if (master == NULL)
		return;
	printf("Info: Cleanup Master Socket\n");
	close(master->fd);
	free(master);
}