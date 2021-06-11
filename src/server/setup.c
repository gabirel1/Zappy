/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** setup
*/

#include "server/server.h"

void init_new_client(client_t *client)
{
    client->is_graphic = false;
    client->is_ia = false;
    memset(client->uuid, 0, 37);
}

int handle_connection(server_t *server, UNSD server_info_t *server_in, \
game_board_t *game, int i)
{
    char *buff = NULL;
    client_t *new = NULL;
    size_t len = sizeof(server->server_address);

    if (i == server->serverfd) {
        new = my_malloc(sizeof(client_t));
        new->fd = accept(i, (struct sockaddr *) &server->server_address, \
        (socklen_t *) &len);
        if (new->fd == -1) {
            fprintf(stderr, "Error while accepting new client\n");
            return ERROR;
        }
        printf("new connection\n");
        FD_SET(new->fd, &server->active_fd_set);
        init_new_client(new);
        add_client(new);
        if (FD_ISSET(new->fd, &server->active_fd_set)) {
            dprintf(new->fd, "WELCOME\n");
        }
    } else {
        buff = read_from_fd(i, &(server->read_fd_set));
        if (!buff) {
            fprintf(stderr, "Error while reading from client\n");
            delete_client_from_list(get_client_by_socket(i));
            return ERROR;
        }
        printf("[%s]\n", buff);
        interpret_cmd(buff, server, game, get_client_by_socket(i));
    }
    return SUCCESS;
}

int launch_server(server_t server, server_info_t *server_in, \
game_info_t *game_info)
{
    game_board_t *game = create_game_board(game_info);
    int res = 0;

    while (my_handler(12, false) == 0) {
        server.read_fd_set = server.active_fd_set;
        server.write_fd_set = server.active_fd_set;
        if (select(FD_SETSIZE, &server.read_fd_set, &server.write_fd_set, \
        NULL, &server.timeout) == -1) {
            fprintf(stderr, "Error while waiting for client\n");
            return ERROR;
        }
        if (my_handler(12, false) != 0)
            break;
        for (int i = 0; i < FD_SETSIZE; i += 1) {
            if (FD_ISSET(i, &server.read_fd_set))
                res = handle_connection(&server, server_in, game, i);
            if (res == ERROR)
                stop_client(i, &server, &res);
        }
    }
    return SUCCESS;
}

int setup_server(server_t server, server_info_t *server_info, game_info_t *game)
{
    if (bind(server.serverfd, (struct sockaddr *) &server.server_address, \
    sizeof(server.server_address)) == -1) {
        fprintf(stderr, "Error while binding socket\n");
        return ERROR;
    }
    if (listen(server.serverfd, server_info->max_client * \
    server_info->nb_teams + 1) == -1) {
        fprintf(stderr, "Error while listening on server");
        return ERROR;
    }
    FD_ZERO(&server.active_fd_set);
    FD_SET(server.serverfd, &server.active_fd_set);
    server.timeout.tv_sec = 1;
    server.timeout.tv_usec = 0;
    return (launch_server(server, server_info, game));
}

int create_server(server_info_t *server_info, game_info_t *game)
{
    server_t server = { 0 };
    int opt = 1;

    server.serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server.serverfd == -1) {
        fprintf(stderr, "ERROR While creating socket\n");
        return ERROR;
    }
    if (setsockopt(server.serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, \
    &opt, sizeof(opt)) == -1) {
        fprintf(stderr, "Error while setting up socket\n");
        return ERROR;
    }
    server.server_address.sin_family = AF_INET;
    server.server_address.sin_addr.s_addr = inet_addr("0.0.0.0");
    server.server_address.sin_port = htons(server_info->port);
    return (setup_server(server, server_info, game));
}