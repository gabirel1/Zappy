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

CXX = g++

DEBUG = g3

TARGET = zappy_server

TARGET_IA = zappy_ai

CFLAGS = -W -Wall -Wextra -I./include

CXXFLAGS = -W -Wall -Wextra -Werror -I./include -g3

LDFLAGS = -luuid

OBJ	=	$(SRC:.c=.o)

OBJ_IA = $(IA:.cpp=.o)

all:	$(OBJ) $(OBJ_IA)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	$(CXX) $(OBJ_IA) -o $(TARGET_IA)

debug:	CFLAGS += -g3

debug:	fclean all

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_IA)

fclean:	clean
	$(RM) $(TARGET)
	$(RM) $(TARGET_IA)

re:	fclean all

