# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfargere <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/19 22:30:14 by cfargere          #+#    #+#              #
#    Updated: 2019/01/10 18:06:01 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CC = gcc

FLAGS = -Wall -Werror -Wextra -o

SRCS =	ft_check.c \
		ft_grid_functions.c \
		ft_solver.c \
		ft_tetriminos.c \
		ft_tetriminos2.c \

OBJ = $(SRC:%.c=%.o)

HEADERS = fillit.h $(LIBFT)/libft.h

LIBFT = ./libft

LIB = ./libft/libft.a

all: $(NAME)
$(NAME):
	@Make -C $(LIBFT) re
	$(CC) $(FLAGS) $(NAME) $(SRCS) $(LIB)

clean:
	@Make -C $(LIBFT) clean

fclean:
	@Make -C $(LIBFT) fclean
	@/bin/rm -f $(NAME)
	@echo "Fillit cleaned"

re: fclean all
