# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/31 13:48:14 by hlombard          #+#    #+#              #
#    Updated: 2019/10/29 11:44:12 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBFTPRINTF = ft_printf/libftprintf.a

LIBFT = ft_printf/libft/libft.a

SRC  =	srcs/ft_colors.c \
		srcs/ft_events_1.c \
		srcs/ft_events_2.c \
		srcs/ft_fdf.c \
		srcs/ft_get_map.c \
		srcs/ft_hooks.c \
		srcs/ft_mlx_init.c \
		srcs/ft_render.c \
		srcs/ft_utils.c \

INC = includes/fdf.h

INC_FOLD = includes/

FT_PRINTF = ft_printf/

MINILIBX = -L ./minilibx -lmlx -framework OpenGL -framework Appkit

MLX_FOLD = -C ./minilibx

CC = gcc

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I $(FT_PRINTF) -I $(INC_FOLD)

all: $(NAME) $(FT_PRINTF)

$(NAME): $(FT_PRINTF) $(INC_FOLD) Makefile $(OBJ)
	@make -C $(FT_PRINTF)
	@make $(MLX_FOLD)
	$(CC) $(OBJ) $(LIBFT) $(LIBFTPRINTF) $(MINILIBX) -o $(NAME)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make -C $(FT_PRINTF) clean
	@make $(MLX_FOLD) clean
	@/bin/rm -Rf $(OBJ)

fclean: clean
	@make -C $(FT_PRINTF) fclean
	@/bin/rm -Rf $(NAME)

re: fclean all
