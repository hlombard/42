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
		includes/hash.h \
		includes/des.h \
		includes/encoding.h \

INC_PRINTF = libft/includes/ft_printf.h

CFLAGS = -Wall -Werror -Wextra -I $(LIBFT) -I $(INC_FOLD) -I $(INC_FOLD_PRINTF)

SRC =	srcs/ft_ssl.c \
		srcs/commands.c \
		srcs/error.c \
		srcs/read.c \
		srcs/write.c \
		srcs/ops32.c \
		srcs/ops64.c \
		srcs/HASH/hash.c \
		srcs/HASH/md5_init.c \
		srcs/HASH/print.c \
		srcs/HASH/md5.c \
		srcs/HASH/sha256.c \
		srcs/HASH/sha256_init.c \
		srcs/HASH/sha512_init.c \
		srcs/HASH/sha512.c \
		srcs/HASH/hash_read.c \
		srcs/HASH/hash_flags.c \
		srcs/ENCODING/base64_enc.c \
		srcs/ENCODING/base64_dec.c \
		srcs/ENCODING/enc_flags.c \
		srcs/ENCODING/enc.c \
		srcs/DES/des.c \
		srcs/DES/des_flags.c \
		srcs/DES/des_encrypt.c \
		srcs/DES/des_decrypt.c \
		srcs/DES/utils.c \
		srcs/DES/des_get.c \
		srcs/DES/keys.c \
		srcs/DES/salt.c \
		srcs/DES/free.c \
		srcs/DES/block.c \

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
