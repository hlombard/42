# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/29 16:28:09 by hlombard          #+#    #+#              #
#    Updated: 2019/11/29 16:28:13 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = gcc

C_GREEN = "\033[32m"
C_BLUE = "\033[36m"
C_BASE = "\033[00m"

LIBFT = ../libft

LIBFT.a = ../libft/libft.a

INC_FOLD = includes

INC = includes/push_swap.h

INC_FOLD_PRINTF = ../libft/includes

INC_PRINTF = ../libft/includes/ft_printf.h

CFLAGS = -Wall -Werror -Wextra -I $(LIBFT) -I $(INC_FOLD) -I $(INC_FOLD_PRINTF)

SRC = srcs/push_swap.c \
	  srcs/verify.c \
	  srcs/chunks.c \
	  srcs/sort_small.c \
	  srcs/sort_big.c \
	  srcs/ops_1.c \
	  srcs/ops_2.c \
	  srcs/ops_3.c \
	  srcs/utils_1.c \
	  srcs/utils_2.c \
	  srcs/utils_3.c

OBJ = $(SRC:.c=.o)

all: libft $(NAME)

libft:
	@make -C $(LIBFT) -s

$(NAME): $(LIBFT) $(INC_FOLD) Makefile $(OBJ)
		@$(CC) $(OBJ) $(LIBFT.a) -o $(NAME)
		@printf "\n\x1b[32mPush_Swap Ready ✔\x1b[0m\n\n"
		@mv push_swap ../push_swap

%.o: %.c $(INC) $(INC_PRINTF)
		@$(CC) $(CFLAGS) -o $@ -c $<
		@echo "file =" $(C_BLUE){ $< } $(C_BASE)

clean:
		@make -C $(LIBFT) clean
		@rm -rf $(OBJ)

fclean: clean
		@make -C $(LIBFT) fclean
		@/bin/rm -f ../$(NAME)
		@echo "\033[31m$(NAME) deleted\033[0m"

re: fclean all
