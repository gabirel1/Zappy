##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

all:	server ai

server:
	make -C ./src/server

ai:
	make -C ./src/ai

graphical:
	make -C ./src/graphical

debug:
	make -C ./src/server debug
	make -C ./src/ai debug

debug_server:
	make -C ./src/server debug

debug_ia:
	make -C ./src/ai debug

clean:
	make -C ./src/server clean
	make -C ./src/ai clean

fclean:	clean
	make -C ./src/server fclean
	make -C ./src/ai fclean

re:	fclean all

.PHONY: server ai