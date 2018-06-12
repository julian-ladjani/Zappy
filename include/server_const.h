/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** 	server_const header file_dir
*/

#ifndef PSU_MYIRC_2017_SERVER_CONST_H
#define PSU_MYIRC_2017_SERVER_CONST_H

#include <stdio.h>

#define MYIRC_USER_DATA_PATH ("./data/user/")
#define MYIRC_USER_DATA_EXTENSION (".ftpuser")
#define MYIRC_MAX_CLIENT (1024)
#define MYIRC_POLL_TIMEOUT (4 * 60 * 1000)
#define MYIRC_EXIT_FAILURE (84)
#define MYIRC_EXIT_CONTINUE (42)
#define MYIRC_EXIT_SUCCESS (0)

typedef FILE file_t;

typedef enum server_state_e {
	MYIRC_SERVER_RUNNING,
	MYIRC_SERVER_STOP,
} server_state_t;

typedef enum user_logged_state_e {
	MYIRC_USER_ALL_STATUS,
	MYIRC_USER_CONNECTED,
	MYIRC_USER_NOT_CONNECTED,
	MYIRC_USER_QUIT,
} user_logged_state_t;

typedef enum user_channel_right_e {
	MYIRC_USER_CHANNEL_USER,
	MYIRC_USER_CHANNEL_OPERATOR,
} user_channel_right_t;

#endif //PSU_MYIRC_2017_SERVER_CONST_H
