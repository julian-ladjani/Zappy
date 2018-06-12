/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** 	user_config_file source file_dir
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "server_struct.h"
#include "server_function.h"
#include "server_const.h"

static int check_file_extension(list_t *elem)
{
	struct dirent *file = elem->elem;
	size_t file_extension_len = strlen(ZAPPY_USER_DATA_EXTENSION);
	size_t file_name_len = strlen(file->d_name);

	if (file_name_len < (file_extension_len + 1))
		return (ZAPPY_EXIT_FAILURE);
	if (strcmp(file->d_name + file_name_len - file_extension_len,
		ZAPPY_USER_DATA_EXTENSION) != 0)
		return (ZAPPY_EXIT_FAILURE);
	return (ZAPPY_EXIT_SUCCESS);
}

static int count_lines(FILE *fp)
{
	int line_nb = 0;
	char pc = '\n';

	for (char c = (char) fgetc(fp); c != EOF; c = (char) fgetc(fp)) {
		if (c == '\n')
			line_nb++;
		pc = c;
	}
	if (pc != '\n')
		line_nb++;
	return (line_nb);
}

static int check_file(list_t *elem)
{
	FILE *fp;
	int line_nb = 0;

	if (check_file_extension(elem) == ZAPPY_EXIT_FAILURE)
		return (ZAPPY_EXIT_FAILURE);
	fp = open_filename_path(ZAPPY_USER_DATA_PATH, ((struct
		dirent *) elem->elem)->d_name, "r");
	if (fp == NULL)
		return (ZAPPY_EXIT_FAILURE);
	line_nb = count_lines(fp);
	fclose(fp);
	if (line_nb == 2)
		return (ZAPPY_EXIT_SUCCESS);
	return (ZAPPY_EXIT_FAILURE);
}

list_t *check_user_file_list(list_t *file_list)
{
	list_t *first_elem = list_get_elem_at_pos(file_list, LIST_FIRST);

	file_list = first_elem;
	while (file_list != NULL) {
		if (file_list->elem == NULL ||
			check_file(file_list) == ZAPPY_EXIT_FAILURE) {
			file_list = list_delete_elem(file_list,
				delete_file_list_elem);
			first_elem = file_list;
		} else
			file_list = file_list->next;
	}
	return (first_elem);
}