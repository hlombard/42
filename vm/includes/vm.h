/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:37:21 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 15:40:00 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <fcntl.h>
# include "libft.h"
# include "struct.h"

# define DEBUG			0
# define TRUE			1
# define FALSE			0
# define SUCCESS		1
# define FAIL			-1
# define FULL			1
# define HALF			2
# define FRST			1
# define SCND			1 << 1
# define THRD			1 << 2

# define BOX_COL_1		COLS / 2 + 15
# define BOX_COL_2		COLS / 5
# define BOX_LINES_1	((LINES / 3) + (LINES / 2)) - 2
# define CMD_LINES		(BOX_LINES_1 / 4)
# define CMD_COLS		(BOX_COL_2 / 2) / 2
# define CMD_STARTY		((CMD_LINES / 2) - 8) - 1
# define CMD_STARTX		(BOX_COL_1 + BOX_COL_2)

# define DARK_GREY		6
# define LIGHT_GREY		7
# define LIGHT_CYAN		5

# define SPACE_BAR		' '
# define QUIT			'q'

# define STR1 			" _____ ___________ _____ _    _  ___ ______ "
# define STR2 			"/  __ \\  _  | ___ \\  ___| |  | |/ _ \\| ___ \\"
# define STR3 			"| /  \\/ | | | |_/ / |__ | |  | / /_\\ \\ |_/ /"
# define STR4 			"| |   | | | |    /|  __|| |/\\| |  _  |    / "
# define STR5 			"| \\__/\\ \\_/ / |\\ \\| |___\\  /\\  / | | | |\\ \\ "
# define STR6			" \\____/\\___/\\_| \\_\\____/ \\/  \\/\\_| |_|_| \\_|"

# define VERBO1 		1
# define VERBO2 		2
# define VERBO3 		4
# define VERBO4			8
# define VERBO5 		16
# define NORMAL 		1
# define INDIRECT 		1 << 1
# define SPECIAL 		1 << 2

extern t_op		g_op_tab[17];
/*
** DEBUG_TOOLS.c
*/

void					print_process_data(t_corewar *cor, int player_nb);
void					print_arena_state(t_corewar *cor);
void					corewar_usage(void);
void					corewar_quit(char *str);

void					ft_print_process(t_process p);
void					ft_print_debug(t_plst *plst, char *op_name, int end);
void					ft_print_plst(t_plst *plst);
void					ft_print_args(t_arg arg);

/*
** NCURSES
*/

void					draw_play(t_corewar *cor);
void					draw_play_1(t_corewar *cor, int x, int x1, int y1);
void					draw_play_2(t_corewar *cor, int x, int x1, int y);
void					draw_pause(t_corewar *cor);

void					draw_arena(t_corewar *cor);
void					draw_window(t_corewar *cor);
void					draw_menu(t_corewar *cor);
void					update_window(t_corewar *cor);

void					ncurse_events(t_corewar *cor);
void					manage_events(t_corewar *cor, int keycode);
void					pause_game(t_corewar *cor);
void					manage_pause(t_corewar *cor, int keycode);

void					fill_border_main(t_corewar *cor);
void					fill_border_menu(t_corewar *cor);
void					fill_border_cmd(t_corewar *cor);

void					init_ncurse(t_corewar *cor);
void					init_colors(void);

void					draw_player_info(t_corewar *cor);
void					draw_infos(t_corewar *cor);
void					draw_banner(t_corewar *cor);
void					draw_command(t_corewar *cor);

void					highlight_process_pc(t_corewar *cor);
void					highlight_it(t_corewar *cor, unsigned int i, int id);
void					set_attributes(t_corewar *cor, unsigned char color,
		int i);
void					unset_attributes(t_corewar *cor, unsigned char color,
		int i);
int						re_adjust_id(int id, t_process *pro);

void					wait_and_close(int wait);
void					free_with_visu(t_corewar *cor);
void					ncurses_show_winner(t_corewar *cor);
void					close_ncurses(t_corewar *cor);
void					end_visu(t_corewar *cor);

/*
** COREWAR.c
*/

void					corewar_end(t_corewar *cor);
void					introducing_contestants(t_corewar *cor);

/*
** PARSING.c
*/

void					parse_arguments(int ac, char **av, t_corewar *cor);
void					parse_arguments_2(t_corewar *cor);

/*
** OPTIONS.C
*/

void					dump_option(t_corewar *cor, char **av, int *i);
void					verbosity_option(t_corewar *cor, char **av, int ac,
		int *i);
void					order_option(t_corewar *cor, char **av, int *i);
void					ft_verbosity_instru(t_corewar *cor, t_plst *plst,
		t_arg arg);
void					ft_verbosity_adv(t_corewar *cor, t_plst *plst);

/*
** ORDERS.c
*/

int						check_doubles_order(t_corewar *cor);
void					attribute_order(t_corewar *cor);
void					reorder_process(t_corewar *cor);
uint32_t				swap_endian(uint32_t val);

/*
** READ_PROCESS.c
*/

void					read_process(char *name, t_corewar *cor, int i);

/*
** GAME.c
*/

void					play(t_corewar *cor);

/*
** CYCLE.C
*/

void					update_cycles(t_corewar *cor);

/*
** UTILITY
*/
t_plst					*ft_plst_init(t_corewar *cor);
void					pc_modulo2(t_plst *plst, int i);
int						pc_modulo(int pc);
void					print_value(t_corewar *cor, int value, int addr,
		t_plst *plst);
int						ft_check_arg_type(t_arg arg, int i, int code1,
		int code2);
void					ft_player_init(t_corewar *cor);
int						ft_get_restricted_addr(int value, int flag);
void					init_plst(t_corewar *cor);

/*
** INSTRUCTIONS
*/

void					inst_add(t_corewar *cor, t_plst *plst);
void					inst_aff(t_corewar *cor, t_plst *plst);
void					inst_and(t_corewar *cor, t_plst *plst);
void					inst_fork(t_corewar *cor, t_plst *plst);
void					inst_ld(t_corewar *cor, t_plst *plst);
void					inst_ldi(t_corewar *cor, t_plst *plst);
void					inst_lfork(t_corewar *cor, t_plst *plst);

void					inst_live(t_corewar *cor, t_plst *plst);
int						ft_get_player_index(t_corewar *cor, int i);

void					inst_lld(t_corewar *cor, t_plst *plst);
void					inst_lldi(t_corewar *cor, t_plst *plst);
void					inst_or(t_corewar *cor, t_plst *plst);
void					inst_st(t_corewar *cor, t_plst *plst);
void					inst_sti(t_corewar *cor, t_plst *plst);
void					inst_sub(t_corewar *cor, t_plst *plst);
void					inst_xor(t_corewar *cor, t_plst *plst);
void					inst_zjmp(t_corewar *cor, t_plst *plst);

/*
** ARG MANIPULATORS
*/

t_arg					ft_arg_init(int nb_arg, int dir_size,
		int addr_restrict, int verbo);
void					ft_get_opcode(t_corewar *cor, t_plst *plst, t_arg *arg);
void					ft_get_args_size(t_arg *arg);
void					ft_get_args(t_corewar *cor, t_plst *plst, t_arg *arg);
void					ft_get_reg_value(t_arg *arg, t_plst *plst, int pos);
int						ft_get_args_size_sum(t_arg	arg);
int						ft_check_reg_index(t_corewar *cor, t_plst *plst,
		t_arg arg);

#endif
