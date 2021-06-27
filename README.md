Zappy's Documentation

```
 ______   _______  _______  __   __  __   __  _______  __    _  _______  _______  _______  ___   _______  __    _ 
|      | |       ||       ||  | |  ||  |_|  ||       ||  |  | ||       ||   _   ||       ||   | |       ||  |  | |
|  _    ||   _   ||       ||  | |  ||       ||    ___||   |_| ||_     _||  |_|  ||_     _||   | |   _   ||   |_| |
| | |   ||  | |  ||       ||  |_|  ||       ||   |___ |       |  |   |  |       |  |   |  |   | |  | |  ||       |
| |_|   ||  |_|  ||      _||       ||       ||    ___||  _    |  |   |  |       |  |   |  |   | |  |_|  ||  _    |
|       ||       ||     |_ |       || ||_|| ||   |___ | | |   |  |   |  |   _   |  |   |  |   | |       || | |   |
|______| |_______||_______||_______||_|   |_||_______||_|  |__|  |___|  |__| |__|  |___|  |___| |_______||_|  |__|
```

## Commands availables : 

- **Server commands**

>- msz
>- bct X Y
>- mct
>- tna
>- ppo n
>- plv n
>- pin n
>- sgt
>- sst N

- **AI commands**

>- Forward
>- Right
>- Left
>- Look
>- Inventory
>- Broadcast text
>- Connect_nbr
>- Fork
>- Eject
>- Take object
>- Set object
>- Incantation



## Server resources :

**Symbols / Meanings**

|SYMBOLS         |Meaning                            |SYMBOLS         |Meaning                              |
|----------------|-----------------------------------|----------------|-------------------------------------|
| X              | width or horizontal position      | n              | player number                       |
| Y              | height or vertical position       | O              | orientation: 1(N), 2(E), 3(S), 4(W) |
| q0             | resource 0 (food) quantity        | L              | player or incantation level         |
| q1             | resource 1 (food) quantity        | e              | egg number                          |
| q2             | resource 2 (food) quantity        | T              | time unit                           |
| q3             | resource 3 (food) quantity        | N              | name of the team                    |
| q4             | resource 4 (food) quantity        | R              | incantation result                  |
| q5             | resource 5 (food) quantity        | M              | message                             |
| q6             | resource 6 (food) quantity        | i              | resource number                     |


## Commands / Responses :

**Server Commands / Responses**

|Command         |Response                                    |
|----------------|--------------------------------------------|
|'msz\n'         |`msz X Y\n`                                 |
|'bct X Y\n'     |`bct X Y q0 q1 q2 q3 q4 q5 q6\n`            |
|'mct\n'         |`bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles`|
|'tna\n'         |`tna N\n * nbr_teams`                       |
|'ppo n\n'       |`"ppo n X Y O\n`                            |
|'plv n\n'       |`plv n L\n`                                 |
|'pin n\n'       |`pin n X Y q0 q1 q2 q3 q4 q5 q6\n`          |
|'sgt\n'         |`sgt T\n`                                   |
|'sst T\n'       |`sst T\n`                                   |




**AI Commands / Responses**

|Command         |Response                                    |
|----------------|--------------------------------------------|
|'Forward'       |`ok`                                        |
|'Right'         |`ok`                                        |
|'Left'          |`ok`                                        |
|'Look'          |`[tile1, tile2,...]`                        |
|'Inventory'     |`[linemate n, sibur n,...]`                 |
|'Broadcast text'|`ok`                                        |
|'Connect_nbr'   |`value`                                     |
|'Fork'          |`ok`                                        |
|'Take object'   |`ok/ko`                                     |
|'Set object'    |`ok/ko`                                     |
|'Incantation'   |`k/ko` (k being the current player's level) |




**Graphical events**

|Server               |Detail                                         |
|---------------------|-----------------------------------------------|
|'pnw #n X Y O L N\n' |connection of a new player                     |
|'pex n\n'            |explusion                                      |
|'pbc n M\n'          |broadcast                                      |
|'pic X Y L n n ...\n'|start of an incantation (by the first player)  |
|'pie X Y R\n'        |end of an incantation                          |
|'pfk n\n'            |egg laying by the player                       |
|'pdr n i\n'          |resource dropping                              |
|'pgt n i\n'          |resource collecting                            |
|'pdi n\n'            |death of a player                              |
|'enw e n X Y\n'      |an egg was laid by a player                    |
|'eht e\n'            |egg hatching                                   |
|'ebo e\n'            |player connection for an egg                   |
|'edi e\n'            |death of an hatched egg                        |
|'seg N\n'            |end of game                                    |
|'smg M\n'            |message from the server                        |
|'suc\n'              |unknown command                                |
|'sbp\n'              | command parameter                             |


## How to use :

- Download the Repository
- Go to the root folder of the repository
- type ```make``` in your shell
- launch the server ```./zappy_server```
- launch the graphical client and connect to the server
- launch the AI ```./zappy_ai -p port -n team_name```


# Server Usage :

```
./zappy_server –help
USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
       port is the port number
       width is the width of the world
       height is the height of the world
       nameX is the name of the team X
       clientsNb is the number of authorized clients per team
       freq is the reciprocal of time unit for execution of actions
```

# AI Usage :

```
./zappy_ai –help
USAGE: ./zappy_ai -p port -n name -h machine
       port is the port number
       name is the name of the team
       machine is the name of the machine; localhost by default
```

# GRAPHICAL CLIENT Usage :

To compile from sources, use this command
```
make -C src/graphical UNITY_PATH=YOUR_PATH_TO_UNITY_BINARY
```
Then you can launch the graphical client binary.
