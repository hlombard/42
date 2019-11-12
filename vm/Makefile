# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 14:43:18 by hlombard          #+#    #+#              #
#    Updated: 2019/09/05 14:43:32 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I $(LIBFT) -I$(OP) -I$(INC_FOLD)
#CFLAGS = -fsanitize=address -Wall -Werror -Wextra -I $(LIBFT) -I$(OP) -I$(INC_FOLD)

C_GREEN = "\033[32m"
C_BLUE = "\033[36m"
C_BASE = "\033[00m"

LIBFT = ../common_files/libft/

OP = ../common_files/

LIBFT.a = ../common_files/libft/libft.a

INC_FOLD = includes/

INC = includes/vm.h \
	  includes/struct.h \

SRC = srcs/corewar.c \
	  srcs/parsing/parsing.c \
	  srcs/parsing/read_process.c \
	  srcs/parsing/order.c \
	  srcs/options/options.c \
	  srcs/options/ft_verbosity_instru.c \
	  srcs/debug/debug_tools.c \
	  srcs/exec/game.c \
	  srcs/exec/cycles.c \
	  srcs/utility/pc_modulo.c \
	  srcs/utility/ft_plst_manipulators.c \
	  srcs/utility/ft_arg_manipulators.c \
	  srcs/utility/ft_arg_manipulators2.c \
	  srcs/utility/ft_check_arg_type.c \
	  srcs/utility/ft_player_init.c \
	  srcs/utility/ft_get_restricted_addr.c \
	  srcs/instructions/inst_add.c \
	  srcs/instructions/inst_sub.c \
	  srcs/instructions/inst_aff.c \
	  srcs/instructions/inst_sti.c \
	  srcs/ncurses/ncurses_init.c \
	  srcs/ncurses/ncurses_fill_border.c \
	  srcs/ncurses/ncurses_utility.c \
	  srcs/ncurses/ncurses_draw.c \
	  srcs/ncurses/ncurses_button.c \
	  srcs/ncurses/ncurses_menu.c \
	  srcs/ncurses/ncurses_events.c \
	  srcs/ncurses/ncurses_close.c \
	  srcs/instructions/inst_and.c \
	  srcs/instructions/inst_st.c \
	  srcs/instructions/inst_ld.c \
	  srcs/instructions/inst_lld.c \
	  srcs/instructions/inst_ldi.c \
	  srcs/instructions/inst_live.c \
	  srcs/instructions/inst_fork.c \
	  srcs/instructions/inst_lfork.c \
	  srcs/instructions/inst_lldi.c \
	  srcs/instructions/inst_zjmp.c \
	  srcs/debug/ft_print_process.c \
	  srcs/instructions/inst_or.c \
	  srcs/instructions/inst_xor.c \
	  

OBJ = $(SRC:.c=.o)

all: libft $(NAME)

libft:
	@make -C $(LIBFT) -s

$(NAME): $(LIBFT) $(INC_FOLD) Makefile $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT.a) -lncurses -o $(NAME)
	@printf "\n\x1b[32mVM Ready ✔\x1b[0m\n\n"

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
