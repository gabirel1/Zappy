##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

all:	server ia

server:	
	make -C ./src/server

ia:
	make -C ./src/ai


debug_server:
	make -C ./src/server debug

debug_ia:
	make -C ./src/ai

clean:
	make -C ./src/server clean
	make -C ./src/ai clean

fclean:	clean
	make -C ./src/server fclean
	make -C ./src/ai fclean

re:	fclean all

.PHONY: server ia