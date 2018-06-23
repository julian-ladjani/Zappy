/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client.h
*/

#ifndef PSU_ZAPPY_2017_CLIENT_H
#define PSU_ZAPPY_2017_CLIENT_H

#define _GNU_SOURCE

#include <sys/poll.h>
#include "map.h"
#include "zappy_socket.h"
#include "parser.h"
#include "circbuff.h"
#include "linked_list.h"
#include <stdarg.h>
#include <stdio.h>

#define ZAPPY_DEBUG (1)

#define ZAPPY_EXIT_FAILURE (2)
#define ZAPPY_EXIT_NOTHING (0)
#define ZAPPY_EXIT_SUCCESS (1)

#define ZAPPY_CLT_DEAD (1)
#define ZAPPY_CLT_READY (2)
#define ZAPPY_CLT_WAITING (0)

#define ZAPPY_IS_KO(s) (strcmp("ko", s) == 0)
#define ZAPPY_IS_OK(s) (strcmp("ok", s) == 0)

typedef struct client_config_s clt_config_t;
typedef int (* clt_func_t)(clt_config_t *);

typedef struct client_parameters_s {
	int port;
	char *machine;
	char *team;
} clt_params_t;

typedef enum ai_modes {
	SEARCHER,
	FOLLOWER,
	SHOUTER,
	EATER,
	LAST_MODE,
	DEBILOUS
} ai_mode_t;

typedef enum sendable_command {
	FORWARD,
	RIGHT,
	LEFT,
	LOOK,
	INVENTORY,
	BROADCAST,
	CONNECT,
	FORK,
	EJECT,
	TAKE,
	SET,
	INCANTATION,
	INCANTATION_WAIT
} send_cmd_t;

typedef struct request_s {
	send_cmd_t cmd_id;
	char *cmd_name;
	uint8_t (*sender)(clt_config_t *client, va_list *av, char s);
} request_t;

typedef struct client_socket_s {
	struct pollfd pollfd[1];
	zappy_socket_t *socket;
	circbuf_t *buf;
	char *active_request;
	char *response_request;
	list_t *broadcasts_queue;
	int long_command;
} clt_socket_t;

typedef struct client_specifications_s {
	size_t id;
	tile_t inventory;
	cardinal_dir_t orientation;
	size_t x;
	size_t y;
	unsigned int level;
	char *team;
	ai_mode_t ai_mode;
	ai_mode_t last_ai_mode;
	int forwarding;
	vec_t target;
	int targeted_incantation_id;
} clt_specs_t;

struct client_config_s {
	map_t *map;
	int status;
	int incantation;
	clt_socket_t *server;
	clt_specs_t *specs;
	int slots;
	request_t send;
};

int prerequest_welcome(clt_config_t *client);
int prerequest_map_size(clt_config_t *client);
int prerequest_team_slots(clt_config_t *client);

int srvrequest_dead(clt_config_t *client);
int srvrequest_message(clt_config_t *client);
int srvrequest_elevation_ko(clt_config_t *client);
int srvrequest_elevation_underway(clt_config_t *client);

uint8_t clt_cmd_get_args_forward(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_right(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_left(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_look(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_inventory(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_broadcast(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_connect_nbr(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_fork(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_eject(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_take(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_set(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_incantation(clt_config_t *client, va_list *, char s);
uint8_t clt_cmd_get_args_incantation_wait(clt_config_t *clt, va_list *, char s);

void show_help_client(void);
int init_server(clt_config_t *client);
int handle_poll(clt_config_t *client);
void launch_ai(clt_config_t *clt);
clt_params_t *client_parse_arguments(int ac, char **av);
double get_tile_ratio(
	clt_config_t *client,
	double (* searcher)(clt_config_t *, ssize_t, ssize_t),
	ssize_t x, ssize_t y);
int get_obj_ratio(clt_config_t *client, tile_t *tile);
int get_food_ratio(clt_config_t *client, tile_t * tile);
int tilecmp(tile_t *t1, tile_t *t2);
double ratio_searcher(clt_config_t *client, ssize_t y, ssize_t x);

void send_active_request(clt_config_t *client, char *msg, ...);
void vsend_active_request(clt_config_t *client, char *msg, va_list *av);
int send_request(send_cmd_t request_id, clt_config_t *client, ...);

int ai_searcher(clt_config_t *client);
int ai_shouter(clt_config_t *client);
int ai_follower(clt_config_t *client);
int condition_pre_incantation(clt_config_t *client);
int condition_end_incantation(clt_config_t *client);
double get_distance_from_tile(clt_config_t *client, ssize_t x, ssize_t y);
void update_target_tile(clt_config_t *clt);
void move_player_to_target(clt_config_t *clt);
void clear_tile_from_ref(clt_config_t *clt, tile_t *tile, tile_t *ref);
void take_obj_from_ref(clt_config_t *clt, tile_t *ref);
void fill_tile_from_inv(clt_config_t *clt, tile_t *tile, tile_t *ref);

#endif /* PSU_ZAPPY_2017_CLIENT_H */