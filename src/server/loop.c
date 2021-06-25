/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** loop
*/

#include "server/server.h"

void update_client_timeout(server_t *server)
{
    struct timeval end = { 0 };
    double secs = 0;

    for (client_t *tmp = *client_container(); tmp; tmp = tmp->next) {
        gettimeofday(&end, NULL);
        secs = (double)(end.tv_usec - tmp->timeout.tv_usec) / 1000000 + \
        (double)(end.tv_sec - tmp->timeout.tv_sec);
        if (secs > 25 && tmp->is_graphic == false && tmp->is_ia == false) {
            FD_CLR(tmp->fd, &(server->active_fd_set));
            delete_client(tmp);
            printf("Client disconnected\n");
        }
    }
}

int server_loop(server_t *server, int res, server_info_t *server_in, \
game_board_t *game)
{
    server->read_fd_set = server->active_fd_set;
    server->write_fd_set = server->active_fd_set;
    if (select(FD_SETSIZE, &server->read_fd_set, &server->write_fd_set, \
    NULL, NULL) == -1) {
        fprintf(stderr, "Error while waiting for client\n");
        return ERROR;
    }
    if (my_handler(12, false) != 0)
        return ERROR;
    for (int i = 0; i < FD_SETSIZE; i += 1) {
        if (FD_ISSET(i, &server->read_fd_set))
            res = handle_connection(server, server_in, game, i);
        if (res == ERROR)
            stop_client(i, server, &res);
    }
    update_cooldown(game, server);
    update_client_timeout(server);
    return SUCCESS;
}