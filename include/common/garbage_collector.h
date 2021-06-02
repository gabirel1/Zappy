/*
** EPITECH PROJECT, 2021
** garbage_collector.h
** File description:
** garbage_collector.h
*/

#ifndef GARBAGE_COLLECTOR_H_
#define GARBAGE_COLLECTOR_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct garbage_s
{
    void *pointer;
    struct garbage_s *next;
} garbage_t;

void *my_malloc(ssize_t size);
void add_garbage(garbage_t **garbage, void *pointer);
void my_destroy(void)__attribute__((destructor(101)));
void *my_realloc(ssize_t size, void *obj);

#endif /* !GARBAGE_COLLECTOR_H_ */
