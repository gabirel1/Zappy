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
	make -C ./src/IA


debug_server:
	make -C ./src/server debug

debug_ia:
	make -C ./src/IA

clean:
	make -C ./src/server clean
	make -C ./src/IA clean

fclean:	clean
	make -C ./src/server fclean
	make -C ./src/IA fclean

re:	fclean all

