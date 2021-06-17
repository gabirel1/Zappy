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
	make -C ./src/AI


debug_server:
	make -C ./src/server debug

debug_ia:
	make -C ./src/AI debug

clean:
	make -C ./src/server clean
	make -C ./src/AI clean

fclean:	clean
	make -C ./src/server fclean
	make -C ./src/AI fclean

re:	fclean all

.PHONY: server ia