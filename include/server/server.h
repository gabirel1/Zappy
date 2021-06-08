/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include "def.h"
#include "common/garbage_collector.h"

typedef struct game_info_s
{
    char **team_names;
    int width;
    int height;
} game_info_t;

typedef struct game_board_s
{

} game_board_t;

typedef struct server_info_s
{
    int port;
    int max_client;
    int nb_teams;
    int freq;
} server_info_t;

typedef struct server_s
{
    int serverfd;
    fd_set write_fd_set;
    fd_set read_fd_set;
    fd_set active_fd_set;
    struct sockaddr_in server_address;
    struct timeval timeout;
} server_t;

typedef struct client_s
{
    int fd;
    bool is_graphic;
    struct client_s *next;
} client_t;

typedef enum item
{
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} item_t;

typedef struct tile_s
{
    int ressources[THYSTAME + 1];
    int posx;
    int posy;
} tile_t;

typedef enum orientation
{
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
} orientation_t;

typedef struct player_s
{
    char uuid[37];
    int posx;
    int posy;
    int level;
    char team_uuid[37];
    orientation_t orientation;
    int inventory[THYSTAME + 1];
    struct player_s *next;
} player_t;

typedef struct team_s
{
    char team_uuid[37];
    char *name;
} team_t;

typedef struct tile_s
{
    int posx;
    int posy;
    int content[THYSTAME + 1];
} tile_t;

typedef struct func_s
{
    char *cmd;
    int (*fun)(char **, server_t *, game_board_t *, client_t *);
} func_t;

char *my_strdup(char *cpy);
int get_tab_len(char *tab[]);
bool is_full_digits(char *string);
void free_tab(char *tab[]);

game_board_t create_game_board(game_info_t *game_info);

bool add_client(client_t *next);
bool delete_client(client_t *client);
client_t *get_client_by_socket(int fd);

player_t **player_container(void);
bool add_player(player_t *next);
bool delete_player(player_t *player);

char *read_from_fd(int fd, fd_set *fd_set);
int interpret_cmd(char *buff, server_t *server, game_board_t *game, \
client_t *client);

int setup_infos(int ac, char *av[], server_info_t *server_info, \
game_info_t *game_info);
void setup_default(server_info_t *s_info, game_info_t *g_info);
int f_case(server_info_t *server_info);
int c_case(server_info_t *server_info);
int y_case(game_info_t *g_info);
int x_case(game_info_t *g_info);



static const func_t func_tab[] = {
    // {"msz", &map_size},
    // {"bct", &tilecontent},
    // {"mct", &all_tiles},
    // {"tna", &all_teams_name},
    // {"ppo", &player_position},
    // {"plv", &player_level},
    // {"pin", &player_inventory},
    // {"sgt", &get_time_unit},
    // {"sst", &set_time_unit},
    // {"Forward", &move_forward},
    // {"Right", &move_right},
    // {"Left", &move_left},
    // {"Look", &look},
    // {"Inventory", &inventory},
    // {"Broadcast text", &broadcast_text},
    // {"Connect_nbr", &connect_nbr},
    // {"Fork", &fork_player},
    // {"Eject", &eject_player},
    // {"Take", &take_object},
    // {"Set", &set_object},
    // {"Incantation", &incantation},
    {NULL, NULL}
};

#endif /* !SERVER_H_ */