##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

IA	=	$(wildcard ./*.cpp)

CXX = g++

TARGET = ../../zappy_ai

CXXFLAGS = -W -Wall -Wextra -Werror

OBJ	=	$(IA:.cpp=.o)

all:	$(TARGET)

$(TARGET) : $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

debug: CXXFLAGS += -g3

debug: fclean all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(TARGET)

re:	fclean all

