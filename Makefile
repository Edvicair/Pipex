# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edvicair <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 21:54:40 by edvicair          #+#    #+#              #
#    Updated: 2022/07/28 02:40:16 by edvicair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CCFLAGS = -Wall -Wextra -Werror
SRC = main.c split.c lib.c get_env.c execve.c
SRC_BONUS = bonus/main.c bonus/lib.c bonus/split.c bonus/get_env.c bonus/execve.c \
bonus/here_doc.c bonus/get_next_line.c bonus/get_next_line_utils.c
OBJ=$(SRC:%.c=%.o)
OBJ_BONUS=$(SRC_BONUS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) 
	gcc -o $(NAME) $(OBJ)

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS) 

fclean: clean
	rm -f $(NAME)

bonus: $(OBJ_BONUS)
	gcc -o $(NAME) $(OBJ_BONUS)

re: fclean all

.PHONY: clean fclean all%  
