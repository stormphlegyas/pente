#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/12 13:41:19 by mmoumini          #+#    #+#              #
#    Updated: 2025/04/11 11:39:06 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY = all, clean, fclean, re

NAME = Gomoku

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++17

LIB_PATH = -L./lib -lFLAC -lsfml-graphics -lvorbis -lfreetype -lsfml-network -lvorbisenc -logg -lsfml-system -lvorbisfile -lsfml-audio -lsfml-window -framework OpenGL -framework AppKit -framework IOKit -framework CoreServices -framework Carbon -framework OpenAL

INC = -I./include

SRC	=	main.cpp						\
		tools.cpp						\
		Timer.cpp						\
		Game.class.cpp					\
		GameAI_virtualTest.class.cpp	\
		Player.class.cpp				\
		Human.class.cpp					\
		AI.class.cpp					\
		Node.cpp					\
		Hit_box.class.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIB_PATH) $(CFLAGS) $(INC)

%.o: %.cpp
	$(CC) -o $@ -c $< $(INC) $(CFLAGS)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean