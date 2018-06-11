/*
** EPITECH PROJECT, 2018
** linked_list_delete
** File description:
** 	linked_list_delete file_dir
*/

#include <linked_list.h>

list_t *list_delete_after(list_t *elem, void (*clean_func)(void *elem))
{
	list_t *elem_after;
	list_t *tmp_elem;
	list_t *elem_end = list_get_elem_at_pos(elem, LIST_END);

	elem_after = elem_end;
	while (elem_after != NULL && elem_after != elem) {
		if (elem_after->next != NULL)
			elem_after->next->prev = elem_after->prev;
		if (elem_after->prev != NULL)
			elem_after->prev->next = elem_after->next;
		if (elem_after->releasable == LIST_RELEASABLE &&
			clean_func != NULL)
			clean_func(elem_after->elem);
		elem_after->elem = NULL;
		tmp_elem = elem_after;
		elem_after = elem_after->prev;
		free(tmp_elem);
	}
	return (list_get_elem_at_pos(elem, LIST_FIRST));
}

list_t *list_delete_before(list_t *elem, void (*clean_func)(void *elem))
{
	list_t *elem_before;
	list_t *tmp_elem;
	list_t *elem_first = list_get_elem_at_pos(elem, LIST_FIRST);

	elem_before = elem_first;
	while (elem_before != NULL && elem_before != elem) {
		if (elem_before->next != NULL)
			elem_before->next->prev = elem_before->prev;
		if (elem_before->prev != NULL)
			elem_before->prev->next = elem_before->next;
		if (elem_before->releasable == LIST_RELEASABLE &&
			clean_func != NULL)
			clean_func(elem_before->elem);
		elem_before->elem = NULL;
		tmp_elem = elem_before;
		elem_before = elem_before->next;
		free(tmp_elem);
	}
	return (elem);
}

list_t *list_delete_elem(list_t *elem, void (*clean_func)(void *elem))
{
	list_t *tmp_elem = list_get_elem_at_pos(elem, LIST_FIRST);

	if (tmp_elem == elem && tmp_elem != NULL)
		tmp_elem = tmp_elem->next;
	if (elem != NULL) {
		if (elem->next != NULL)
			elem->next->prev = elem->prev;
		if (elem->prev != NULL)
			elem->prev->next = elem->next;
		if (elem->releasable == LIST_RELEASABLE && clean_func != NULL)
			clean_func(elem->elem);
		free(elem);
	}
	return (tmp_elem);
}

list_t *list_delete_all(list_t *list, void (*clean_func)(void *elem))
{
	list_t *elem;
	list_t *tmp_elem;

	list = list_get_elem_at_pos(list, LIST_FIRST);
	elem = list;
	while (elem != NULL) {
		if (elem->next != NULL)
			elem->next->prev = elem->prev;
		if (elem->prev != NULL)
			elem->prev->next = elem->next;
		if (elem->releasable == LIST_RELEASABLE && clean_func != NULL)
			clean_func(elem->elem);
		tmp_elem = elem;
		elem = elem->next;
		free(tmp_elem);
	}
	return (NULL);
}

list_t *list_delete_at_pos(list_t *list,
	int pos,
	void (*clean_func)(void *elem))
{
	if (list == NULL)
		return (NULL);
	switch (pos) {
		case LIST_AFTER:
			return (list_delete_after(list, clean_func));
		case LIST_BEFORE:
			return (list_delete_before(list, clean_func));
		case LIST_ALL:
			return (list_delete_all(list, clean_func));
		default:
			return (list_delete_elem(
				list_get_elem_at_pos(list, pos), clean_func));
	}
}
