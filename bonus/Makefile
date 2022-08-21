# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edvicair <edvicair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 21:54:40 by edvicair          #+#    #+#              #
#    Updated: 2022/08/15 20:22:05 by edvicair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS = pipex_bonus
CCFLAGS = -Wall -Wextra -Werror
SRC_BONUS = main.c lib.c split.c get_env.c execve.c \
here_doc.c get_next_line.c get_next_line_utils.c pipex.c \
free.c
OBJ_BONUS=$(SRC_BONUS:%.c=%.o)

all: $(NAME_BONUS)

.c.o:
	gcc $(CCFLAGS) -c $< -o ${<:.c=.o}

clean:
	rm -f $(OBJ_BONUS) 

$(NAME_BONUS): $(OBJ_BONUS) 
	gcc -o $(NAME_BONUS) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME_BONUS)

bonus: $(OBJ_BONUS)
	gcc -o $(NAME_BONUS) $(OBJ_BONUS) -g

re: fclean all

re_bonus: fclean bonus

.PHONY: clean fclean all re bonus re_bonus%
