# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/28 18:00:13 by hlombard          #+#    #+#              #
#    Updated: 2019/11/28 18:42:13 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C checker_dir
	@make -C push_swap_dir

clean:
	@make -C checker_dir clean
	@make -C push_swap_dir clean

fclean:
	@make -C checker_dir fclean
	@make -C push_swap_dir fclean

re: fclean all
