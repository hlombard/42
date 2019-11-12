# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlombard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 14:45:46 by hlombard          #+#    #+#              #
#    Updated: 2019/09/05 14:45:53 by hlombard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C assembler
	@make -C vm
	@make -C disasm
	@mv ./vm/corewar ./corewar
	@mv ./assembler/asm ./asm
	@mv ./disasm/disassembler ./disassembler

clean:
	@make -C assembler clean
	@make -C vm clean
	@make -C disasm clean

fclean:
	@make -C assembler fclean
	@make -C vm fclean
	@make -C disasm fclean
	@rm -rf asm
	@rm -rf corewar
	@rm -rf disassembler

re: fclean all
