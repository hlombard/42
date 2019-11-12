# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ratin <ratin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 18:46:26 by ratin             #+#    #+#              #
#    Updated: 2019/09/05 14:44:45 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = disassembler

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I $(LIBFT) -I$(OP) -I$(INC_FOLD)
#CFLAGS = -fsanitize=address -Wall -Werror -Wextra -I $(LIBFT) -I$(OP) -I$(INC_FOLD)

C_GREEN = "\033[32m"
C_BLUE = "\033[36m"
C_BASE = "\033[00m"

LIBFT = ../common_files/libft/

OP = ../common_files/

LIBFT.a = ../common_files/libft/libft.a

INC_FOLD = includes/

INC = includes/disassembler.h

SRC = srcs/disassembler.c \
	srcs/parsing/read_process.c \
	srcs/parsing/read_process1.c \
	srcs/parsing/create_file.c \
	srcs/parsing/print_file.c \
	srcs/parsing/create_list.c \
	srcs/parsing/get_params.c \
	srcs/parsing/get_arg.c \

OBJ = $(SRC:.c=.o)

all: libft $(NAME)

libft:
	@make -C $(LIBFT) -s

$(NAME): $(LIBFT) $(INC_FOLD) Makefile $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT.a) -o $(NAME)
	@printf "\n\x1b[32mDISASSEMBLER Ready ✔\x1b[0m\n\n"

%.o: %.c $(INC) $(OP)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "file =" $(C_GREEN){ $< } $(C_BASE)

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@/bin/rm -f $(NAME)
	@echo "\033[31m$(NAME) deleted\033[0m"

re: fclean all

.PHONY: all fclean clean re
