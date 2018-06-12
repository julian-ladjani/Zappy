/*
** EPITECH PROJECT, 2018
** Julian's library
** File description:
** 	arg_parser header file
*/

#ifndef PSU_ZAPPY_2017_ARG_PARSER_H
#define PSU_ZAPPY_2017_ARG_PARSER_H

#include <unistd.h>
#include <regex.h>

#define ARG_PARSER_UNLIMITED (0)
#define ARG_PARSER_SUCCESS (0)
#define ARG_PARSER_FAILURE (1)

typedef enum arg_parser_interval_e {
	ARG_PARSER_OPEN,
	ARG_PARSER_CLOSE,
	ARG_PARSER_SEMI_OPEN_LEFT,
	ARG_PARSER_SEMI_OPEN_RIGHT
} arg_parser_interval_t;

typedef struct arg_parser_output_s {
	void *args;
	size_t nb_arg;
	char *next_arg;
} arg_parser_output_t;


typedef struct arg_parser_input_s {
	char *start_regexp;
	char *stop_regexp;
	size_t offset;
	char **argv;
	arg_parser_interval_t interval;
	void *(*tokenize_func)(arg_parser_output_t *output, char *data);
} arg_parser_input_t;

//do not use this functions
void cleanup_regex(regex_t *regex);
regex_t *init_regex(char *regex_string);
int argument_check_regex(char *string, regex_t *regex);
void *cleanup_argument_parsing(arg_parser_output_t *output,
	regex_t *search_regex, regex_t *stop_regex, void *return_value);
void cleanup_regex(regex_t *regex);
regex_t *init_regex(char *regex_string);
arg_parser_output_t *initialise_arg_parser_output(void);

//use this
arg_parser_input_t *initialise_arg_parser_input(void);

#endif //PSU_ZAPPY_2017_ARG_PARSER_H
