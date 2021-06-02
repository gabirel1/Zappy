##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = 	$(wildcard src/server/*.c)	\

CC = gcc

DEBUG = g3

TARGET = zappy_server

CFLAGS = -W -Wall -Wextra -I./include

LDFLAGS =

OBJ	=	$(SRC:.c=.o)

all:	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

debug:	CFLAGS += -g3

debug:	fclean all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(TARGET)

re:	fclean all

