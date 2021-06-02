/*
** EPITECH PROJECT, 2021
** garbage_collector.c
** File description:
** garbage_collector.c
*/

#include "common/garbage_collector.h"

garbage_t **get_garbage_list(void)
{
    static garbage_t *garbage = NULL;

    return (&garbage);
}

void add_garbage(garbage_t **garbage, void *ptr)
{
    garbage_t *cp = malloc(sizeof(garbage_t));

    cp->pointer = ptr;
    cp->next = *garbage;
    *garbage = cp;
}

void my_destroy(void)
{
    garbage_t *cp = NULL;
    garbage_t *garbage = *get_garbage_list();

    while (garbage) {
        cp = garbage;
        free(cp->pointer);
        garbage = garbage->next;
        free(cp);
    }
}

void *my_realloc(ssize_t size, void *obj)
{
    void *ptr = my_malloc(size);
    size_t len = sizeof(obj);

    if (obj) {
        memcpy(ptr, obj, len);
    }
    return ptr;
}

void *my_malloc(ssize_t size)
{
    void *pointer = malloc(size);
    char *cpy = pointer;

    add_garbage(get_garbage_list(), pointer);
    for (ssize_t i = 0; i < size; i += 1)
        cpy[i] = 0;
    return (pointer);
}
