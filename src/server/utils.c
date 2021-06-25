/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** utils
*/

#include "server/server.h"

char *read_from_fd(int fd, fd_set *fd_set)
{
    char *buff = NULL;
    FILE *stream = NULL;
    size_t len = 0;
    ssize_t n = 0;

    if (!FD_ISSET(fd, fd_set))
        return NULL;
    stream = fdopen(dup(fd), "r");
    n = getline(&buff, &len, stream);
    fclose(stream);
    if (n < 0) {
        free(buff);
        return NULL;
    }
    buff[n - 1] = 0;
    return buff;
}

void delete_client_from_list(client_t *client)
{
    if (client != NULL)
        if (delete_client(client) == false)
            printf("couldn't delete client\n");
}

void stop_client(int fd, server_t *server, int *res)
{
    close(fd);
    FD_CLR(fd, &server->active_fd_set);
    *res = 0;
    printf("one connection closed\n");
}

char **copy_tab(char **dest, char **src)
{
    int len = get_tab_len(src);
    int index = 0;

    dest = malloc(sizeof(char *) * (len + 1));
    if (!dest)
        return NULL;
    for (; index < len; index++)
        dest[index] = strdup(src[index]);
    dest[index] = NULL;

    return dest;
}