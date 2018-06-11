/*
** EPITECH PROJECT, 2018
** list_clean
** File description:
** 	list_clean file_dir
*/

#include "linked_list.h"

list_t *list_clean_after(list_t *elem)
{
	list_t *elem_after;
	list_t *elem_end = list_get_elem_at_pos(elem, LIST_END);

	elem_after = elem_end;
	while (elem_after != NULL && elem_after != elem) {
		if (elem_after->releasable == LIST_RELEASABLE)
			free(elem_after->elem);
		elem_after->elem = NULL;
		elem_after = elem_after->prev;
	}
	return (list_get_elem_at_pos(elem, LIST_FIRST));
}

list_t *list_clean_before(list_t *elem)
{
	list_t *elem_before;
	list_t *elem_first = list_get_elem_at_pos(elem, LIST_FIRST);

	elem_before = elem_first;
	while (elem_before != NULL && elem_before != elem) {
		if (elem_before->releasable == LIST_RELEASABLE)
			free(elem_before->elem);
		elem_before->elem = NULL;
		elem_before = elem_before->next;
	}
	return (elem_first);
}

list_t *list_clean_elem(list_t *elem)
{
	if (elem != NULL) {
		if (elem->releasable == LIST_RELEASABLE)
			free(elem->elem);
		elem->elem = NULL;
	}
	return (list_get_elem_at_pos(elem, LIST_FIRST));
}

list_t *list_clean_all(list_t *list)
{
	list_t *elem;

	list = list_get_elem_at_pos(list, LIST_FIRST);
	elem = list;
	while (elem != NULL) {
		if (elem->releasable == LIST_RELEASABLE)
			free(elem->elem);
		elem->elem = NULL;
		elem = elem->next;
	}
	return (list);
}

list_t *list_clean_at_pos(list_t *list, int pos)
{
	if (list == NULL)
		return (NULL);
	switch (pos) {
		case LIST_AFTER:
			return (list_clean_after(list));
		case LIST_BEFORE:
			return (list_clean_before(list));
		case LIST_ALL:
			return (list_clean_all(list));
		default:
			return (list_clean_elem(
				list_get_elem_at_pos(list, pos)));
	}
}
