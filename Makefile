# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/05 16:09:00 by hlombard          #+#    #+#              #
#    Updated: 2019/10/29 19:16:47 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc

LIBFT = libft/

LIBFT.a = libft/libft.a

INC_FOLD = includes/

INC = includes/fractol.h

MLX = -L ./minilibx -lmlx -framework OpenGL -framework Appkit

CFLAGS = -Wall -Werror -Wextra -O3 -flto -I $(LIBFT) -I $(INC_FOLD)

SRC = srcs/fractol.c \
	  srcs/init.c	\
	  srcs/init_types.c \
	  srcs/keyboard_events.c \
	  srcs/mouse_events.c \
	  srcs/gpu.c \
	  srcs/utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME) $(LIBFT)

$(NAME): $(LIBFT) $(INC_FOLD) Makefile $(OBJ)
		@make -C $(LIBFT)
		@make -C minilibx
		$(CC) -I /usr/local/include $(OBJ) $(LIBFT.a) $(MLX) -framework OpenCL -o $(NAME)
		@echo "\033[32m$(NAME) created ! \033[0m"

%.o: %.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		@make -C $(LIBFT) clean
		@make -C minilibx clean
		@rm -rf $(OBJ)

fclean: clean
		@make -C $(LIBFT) fclean
		@/bin/rm -f $(NAME)
		@echo "\033[31m$(NAME) deleted\033[0m"

re: fclean all

