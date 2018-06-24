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
#include <time.h>
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
	int ret;

	server_config->state = ZAPPY_SERVER_RUNNING;
	SERVER_CONFIG = server_config;
	signal(SIGINT, server_exit_catch);
	signal(SIGPIPE, SIG_IGN);
	printf("Info: Start Listening Client\n");
	listen_for_client(server_config);
	server_timer_start(server_config);
	while (server_config->state != ZAPPY_SERVER_STOP) {
		ret = poll(server_config->poll_fd, server_config->nfds, 1);
		if (ret < 0)
			continue;
		else if (ret > 0)
			poll_loop(server_config);
		exec_pending_command(server_config);
		server_timer_end(server_config);
		user_disconect_when_quit_state(server_config);
	}
	cleanup_server_exit(server_config, ZAPPY_EXIT_SUCCESS);
}
