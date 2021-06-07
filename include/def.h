/*
** EPITECH PROJECT, 2021
** def.h
** File description:
** def.h
*/

#ifndef DEF_H_
#define DEF_H_

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <sys/wait.h>
#include <dlfcn.h>
#include <uuid/uuid.h>
#include <signal.h>

#define SUCCESS 0
#define ERROR -1
#define FAILURE 84

int help_func(int error_code);
char **str_to_word_array(char *str, char *delim);

#endif /* !DEF_H_ */
