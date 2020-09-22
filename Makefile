NAME = ft_ssl

CC = gcc

C_RED = "\033[31m"
C_GREEN = "\033[32m"
C_YELLOW = "\033[33m"
C_BLUE = "\033[36m"
C_BASE = "\033[00m"


LIBFT = libft
LIBFT.a = libft/libft.a
INC_FOLD = includes
INC_FOLD_PRINTF = libft/includes

INC =	includes/ft_ssl.h \
		includes/constants.h

INC_PRINTF = libft/includes/ft_printf.h

CFLAGS = -Wall -Werror -Wextra -I $(LIBFT) -I $(INC_FOLD) -I $(INC_FOLD_PRINTF)

SRC =	srcs/ft_ssl.c \
		srcs/md5_init.c \
		srcs/args.c \
		srcs/flags.c \
		srcs/read.c \
		srcs/print.c \
		srcs/error.c \
		srcs/md5.c \
		srcs/sha256.c \
		srcs/sha256_init.c \
		srcs/sha512_init.c \
		srcs/sha512.c \
		srcs/ops32.c \
		srcs/ops64.c \

OBJ = $(SRC:.c=.o)

all: $(NAME) $(LIBFT)

$(NAME): $(LIBFT) $(INC_FOLD) Makefile $(OBJ)
		@make -C $(LIBFT) -s
		@$(CC) $(OBJ) $(LIBFT.a) -o $(NAME)
		@echo $(C_GREEN) "\n\n[$(NAME)] $(NAME) Ready ✔" $(C_BASE)

%.o: %.c $(INC) $(INC_PRINTF)
		@$(CC) $(CFLAGS) -o $@ -c $<
		@echo "[$(NAME)] file =" $(C_BLUE){ $< } $(C_BASE)

clean:
		@make -C $(LIBFT) clean -s
		@rm -rf $(OBJ)
		@echo $(C_YELLOW) "[$(NAME)] OBJ Files Cleaned" $(C_BASE)

fclean: clean
		@rm -f libft/libft.a
		@echo $(C_RED) "[libft] libft.a Deleted" $(C_BASE)
		@/bin/rm -f $(NAME)
		@echo $(C_RED) "[$(NAME)] $(NAME) Deleted" $(C_BASE)

re: fclean all
