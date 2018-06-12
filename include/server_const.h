/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	server_const header file_dir
*/

#ifndef PSU_ZAPPY_2017_SERVER_CONST_H
#define PSU_ZAPPY_2017_SERVER_CONST_H

#include <stdio.h>

#define ZAPPY_USER_DATA_PATH ("./data/user/")
#define ZAPPY_USER_DATA_EXTENSION (".ftpuser")
#define ZAPPY_MAX_CLIENT (1024)
#define ZAPPY_POLL_TIMEOUT (4 * 60 * 1000)
#define ZAPPY_EXIT_FAILURE (84)
#define ZAPPY_EXIT_CONTINUE (42)
#define ZAPPY_EXIT_SUCCESS (0)

typedef FILE file_t;

typedef enum server_state_e {
	ZAPPY_SERVER_RUNNING,
	ZAPPY_SERVER_STOP,
} server_state_t;

typedef enum user_logged_state_e {
	ZAPPY_USER_ALL_STATUS,
	ZAPPY_USER_CONNECTED,
	ZAPPY_USER_NOT_CONNECTED,
	ZAPPY_USER_QUIT,
} user_logged_state_t;

typedef enum user_channel_right_e {
	ZAPPY_USER_CHANNEL_USER,
	ZAPPY_USER_CHANNEL_OPERATOR,
} user_channel_right_t;

#endif //PSU_ZAPPY_2017_SERVER_CONST_H