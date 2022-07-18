# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edvicair <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 21:54:40 by edvicair          #+#    #+#              #
#    Updated: 2022/06/13 11:47:19 by edvicair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CCFLAGS = -Wall -Wextra -Werror
SRC = main.c split.c lib.c get_env.c execve.c
OBJ=$(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) 
	gcc -o $(NAME) $(OBJ)

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all%  
