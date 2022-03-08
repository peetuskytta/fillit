/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:41:50 by igaplich          #+#    #+#             */
/*   Updated: 2022/03/01 17:49:42 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <fcntl.h>

typedef struct s_tetlist
{
	char				**map;
	char				symbol;
	int					x_pos[4];
	int					y_pos[4];
	int					x_map[4];
	int					y_map[4];
	struct s_tetlist	*next;
}	t_tetlist;

/*
 * ---------ERROR HANDLING----------
*/
void		error_print(void);

/*
** -------TETROMINO MANIPULATION-------
*/
t_tetlist	*tetr_split(char *buff);
void		tetr_create(t_tetlist **head, char **split, char map_sym, int *row);
void		tetr_manipulation(t_tetlist *head, int x_min, int y_min, int x);
void		tetr_move(char **map, int *x_min, int *y_min, int x);
void		save_coord(t_tetlist *head, int x, int y);
void		tetr_link(t_tetlist **head, t_tetlist *tetr);

/*
** -----------PRIMARY CHECKS-----------
*/
int			primary_checks(int argc, char **argv, char *buff);
int			symb_amount_check(char *buff, int hash_c, int i, int tetr_last);
void		arg_amount_check(int argc);
void		line_len_check(char *buff, int len_count, int row_count, size_t i);
void		shape_check(char *buff, int i, int bonds, int piece);
void		reading_file(char *buff, char **argv);

/*
** ---------TETROMINO SOLVING----------
*/
char		**solver(t_tetlist *head, int pieces);
char		**map_create(int len);
int			inserting_tetr(char **solution, t_tetlist *tetr, int x, int y);
int			fillit_algo(t_tetlist *head, int pieces, int size, char **fill_map);
int			map_iterate(t_tetlist *tetr, char **solution, char *symb, int len);
int			map_minsize(int pieces);

/*
** -----------MEMORY FREEING-----------
*/
void		del_tetr(t_tetlist *tetr, char **fill_map);
void		del_arr(char **to_clean);
void		del_list(t_tetlist *head);

#endif
