/*
** EPITECH PROJECT, 2018
** linked_list_conditional
** File description:
** 	linked_list_conditional file_dir
*/

#include "linked_list.h"

list_t *list_get_elem_if_exist(list_t *list, list_t *elem)
{
	if (elem != NULL && list_get_elem(list, elem))
		return (elem);
	return (NULL);
}

list_t *list_get_elem_by_search(list_t *list, void *criteria,
	int (*search_func)(void *elem, void *criteria))
{
	list = list_get_first(list);
	while (list != NULL) {
		if (search_func(list->elem, criteria) > 0)
			return (list);
		list = list->next;
	}
	return (NULL);
}

int list_count_elem_by_search(list_t *list, void *criteria,
	int (*search_func)(void *elem, void *criteria))
{
	list = list_get_first(list);
	int nb_elem = 0;

	while (list != NULL) {
		if (search_func(list->elem, criteria) > 0)
			nb_elem++;
		list = list->next;
	}
	return (nb_elem);
}

list_t *list_get_next_elem_by_search(list_t *elem, void *criteria,
	int (*search_func)(void *elem, void *criteria))
{
	if (elem != NULL)
		elem = elem->next;
	while (elem != NULL) {
		if (search_func(elem->elem, criteria) > 0)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

list_t *list_get_elem_if_not_exist(list_t *list, list_t *elem)
{
	if (elem == NULL || list_get_elem(list, elem) == NULL)
		return (elem);
	return (NULL);
}