/*
** EPITECH PROJECT, 2018
** linked_list_get
** File description:
** 	linked_list_get file_dir
*/

#include "linked_list.h"

list_t *list_get_elem(list_t *list, list_t *elem)
{
	list = list_get_elem_at_pos(list, LIST_FIRST);

	while (list != NULL && list != elem)
		list = list->next;
	return (list);
}

list_t *list_get_elem_with_content(list_t *list, void *elem)
{
	list = list_get_elem_at_pos(list, LIST_FIRST);

	while (list != NULL && list->elem != elem)
		list = list->next;
	return (list);
}

list_t *list_get_first(list_t *list)
{
	while (list != NULL && list->prev != NULL)
		list = list->prev;
	return (list);
}

list_t *list_get_elem_at_pos(list_t *list, int pos)
{
	if (list == NULL)
		return (NULL);
	switch (pos) {
		case LIST_AFTER:
			return (list_get_elem_if_exist(list, list->next));
		case LIST_BEFORE:
			return (list_get_elem_if_exist(list, list->prev));
		case LIST_END:
			return (list_get_elem_at_pos(list, list_size
				(list)));
		case LIST_FIRST:
			return (list_get_first(list));
		default:
			while (list->next != NULL && (pos--) > 0)
				list = list->next;
			break;
	}
	return (list);
}
