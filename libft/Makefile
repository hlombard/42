# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/14 22:03:59 by hlombard          #+#    #+#              #
#    Updated: 2019/07/05 16:05:36 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Werror -Wextra -Iincludes

SRCS =		ft_atoi.c		\
		  ft_bzero.c	\
		  ft_countword.c	\
		  ft_isalnum.c	\
		  ft_isalpha.c	\
		  ft_isascii.c	\
		  ft_isdigit.c	\
		  ft_isprint.c	\
		  ft_itoa.c		\
		  ft_lstadd.c	\
		  ft_lstdel.c	\
		  ft_lstdelone.c	\
		  ft_lstiter.c	\
		  ft_lstmap.c	\
		  ft_lstnew.c	\
		  ft_memalloc.c	\
		  ft_memccpy.c	\
		  ft_memchr.c	\
		  ft_memcmp.c	\
		  ft_memcpy.c	\
		  ft_memdel.c	\
		  ft_memmove.c	\
		  ft_memset.c	\
		  ft_putchar.c	\
		  ft_putchar_fd.c	\
		  ft_putendl.c	\
		  ft_putendl_fd.c	\
		  ft_putnbr.c	\
		  ft_putnbr_fd.c	\
		  ft_putstr.c	\
		  ft_putstr_fd.c	\
		  ft_strcat.c	\
		  ft_strchr.c	\
		  ft_strclr.c	\
		  ft_strcmp.c	\
		  ft_strcpy.c	\
		  ft_strdel.c	\
		  ft_strdup.c	\
		  ft_strequ.c	\
		  ft_striter.c	\
		  ft_striteri.c	\
		  ft_strjoin.c	\
		  ft_strlcat.c	\
		  ft_strlen.c	\
		  ft_strmap.c	\
		  ft_strmapi.c	\
		  ft_strncat.c	\
		  ft_strncmp.c	\
		  ft_strncpy.c	\
		  ft_strnequ.c	\
		  ft_strnew.c	\
		  ft_strnstr.c	\
		  ft_strrchr.c	\
		  ft_strsplit.c	\
		  ft_strstr.c	\
		  ft_strsub.c	\
		  ft_strtrim.c	\
		  ft_tolower.c	\
		  ft_toupper.c	\
		  ft_itoa_base.c \
		  ft_itoa.c \
		  get_next_line.c \
		  ft_printf.c \
		  ft_utility.c \
		  ft_utility2.c \
		  ft_utility3.c \
		  ft_utility4.c \
		  ft_utility5.c \
		  ft_draw.c \
		  ft_parse_flags.c \
		  ft_convert_s.c \
		  ft_convert_p.c \
		  ft_convert_o.c \
		  ft_convert_d_and_i.c \
		  ft_convert_c.c \
		  ft_convert_x_and_majx.c \
		  ft_convert_u.c \
		  ft_convert_b.c \
		  ft_convert_float.c \
		  ft_convert_percentage.c \
		  ft_convert_nb_word.c \
		  ft_colors.c \
		  ft_atoll.c \
		  ft_strmaxint.c \

INCLUDES = libft.h includes/ft_printf.h

OBJ = $(SRCS:.c=.o)

all: $(NAME) includes/

$(NAME): $(OBJ)
	@ar rcs $(NAME) $^
	@echo "Libft Ready !"

%.o: %.c $(INCLUDES)
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@/bin/rm -Rf $(OBJ)
	@echo "OBJ Files Cleaned"

fclean: clean
	@/bin/rm -Rf $(NAME)
	@echo "Libft.a Deleted"

re: fclean all
