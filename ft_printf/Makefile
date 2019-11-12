# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/28 22:54:17 by hlombard          #+#    #+#              #
#    Updated: 2019/03/28 13:46:43 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = ft_printf.h

LIBFT = ./libft/

LIBFT.a = libft/libft.a

INCLUDES = ft_printf.h

SOURCES =	ft_printf.c \
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


LIBFT_SRCS = ft_putstr.c \
			 ft_strlen.c \
			 ft_atoi.c \
			 ft_putchar.c \
			 ft_isdigit.c \
			 ft_putchar_fd.c \
			 ft_strncmp.c \
			 ft_putnbr.c \
			 ft_putnbr_fd.c \
			 ft_putstr_fd.c \
			 ft_countword.c \
			 ft_strcat.c \



	



LIBFT_OBJ = $(LIBFT)ft_putstr.o \
			$(LIBFT)ft_strlen.o \
			$(LIBFT)ft_atoi.o \
			$(LIBFT)ft_putchar.o \
			$(LIBFT)ft_isdigit.o \
			$(LIBFT)ft_putchar_fd.o \
			$(LIBFT)ft_strncmp.o \
			$(LIBFT)ft_putnbr.o \
			$(LIBFT)ft_putnbr_fd.o \
			$(LIBFT)ft_putstr_fd.o \
			$(LIBFT)ft_countword.o \
			$(LIBFT)ft_strcat.o \





CFLAGS = -Wall -Werror -Wextra

OBJ = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT) re
	@ar rcs $(NAME) $(OBJ) $(LIBFT_OBJ)
	@echo "Libftprintf.a has been successfully created"

clean:
	@make -C $(LIBFT) clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all
