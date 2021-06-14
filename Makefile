##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = 	$(wildcard src/server/*.c)	\
		$(wildcard src/server/commands/*.c)	\
		$(wildcard src/common/*.c)	\

IA	=	$(wildcard src/IA/*.cpp)

CC = gcc

PP = g++

DEBUG = g3

TARGET = zappy_server

TARGET_IA = IA

CFLAGS = -W -Wall -Wextra -I./include

LDFLAGS = -luuid

OBJ	=	$(SRC:.c=.o)

all:	$(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	$(PP) $(IA) -o $(TARGET_IA)

debug:	CFLAGS += -g3

debug:	fclean all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(TARGET)
	$(RM) $(TARGET_IA)

re:	fclean all

