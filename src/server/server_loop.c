/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_loop source file
*/

#include <sys/socket.h>
#include <sys/poll.h>
#include <netdb.h>
#include <signal.h>
#include "server_struct.h"
#include "server_function.h"

static server_config_t *SERVER_CONFIG;

static void listen_for_client(server_config_t *server_config)
{
	if (listen(server_config->master->fd, ZAPPY_MAX_CLIENT) ==
		-1) {
		printf("Error: When Listening Clients\n");
		cleanup_server_exit(server_config,
			ZAPPY_EXIT_FAILURE);
	}
}

void server_exit_catch(int sig)
{
	if (sig != SIGINT)
		return;
	printf("Info: Receiving Kill Signal, Proceed\n");
	cleanup_server_exit(SERVER_CONFIG, ZAPPY_EXIT_SUCCESS);
}

void server_main_loop(server_config_t *server_config)
{
	server_config->state = ZAPPY_SERVER_RUNNING;
	int ret;

	SERVER_CONFIG = server_config;
	signal(SIGINT, server_exit_catch);
	printf("Info: Start Listening Client\n");
	listen_for_client(server_config);
	while (server_config->state != ZAPPY_SERVER_STOP) {
		ret = poll(server_config->poll_fd, server_config->nfds,
			ZAPPY_POLL_TIMEOUT);
		timer_set_current_time(server_config->cur_time);
		if (ret < 0)
			break;
		else if (ret > 0)
			poll_loop(server_config);
		exec_pending_command(server_config);
		usleep(200);
	}
	cleanup_server_exit(server_config, ZAPPY_EXIT_SUCCESS);
}
