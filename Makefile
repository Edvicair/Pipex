# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 21:54:40 by edvicair          #+#    #+#              #
#    Updated: 2022/08/21 13:28:34 by edvicair         ###   ########.fr        #
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

.c.o:
	gcc $(CCFLAGS) -c $< -o ${<:.c=.o}

clean:
	rm -f $(OBJ)
	make -s -C bonus clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	make -s -C bonus fclean

bonus:
	make -C  bonus && cd bonus && cp pipex_bonus ..

re: fclean all

re_bonus: fclean bonus

.PHONY: clean fclean all re bonus re_bonus%
