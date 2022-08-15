# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 21:54:40 by edvicair          #+#    #+#              #
#    Updated: 2022/08/15 16:01:40 by edvicair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CCFLAGS = -Wall -Wextra -Werror
SRC = main.c split.c lib.c get_env.c execve.c
SRC_BONUS = bonus/main.c bonus/lib.c bonus/split.c bonus/get_env.c bonus/execve.c \
bonus/here_doc.c bonus/get_next_line.c bonus/get_next_line_utils.c bonus/pipex.c \
bonus/free.c
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
	rm -f $(NAME_BONUS)

bonus: $(OBJ_BONUS)
	gcc -o $(NAME_BONUS) $(OBJ_BONUS) -g

re: fclean all

re_bonus: fclean bonus

.PHONY: clean fclean all re bonus re_bonus%
