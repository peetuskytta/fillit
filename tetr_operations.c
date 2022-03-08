/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetr_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 12:01:48 by igaplich          #+#    #+#             */
/*   Updated: 2022/03/01 17:40:23 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * This function splits the *buff read from the file descriptor into
 * individual strings, 4 strings in each tetrimino.
*/
t_tetlist	*tetr_split(char *buff)
{
	int			row;
	char		**split;
	char		map_letter;
	t_tetlist	*head;

	head = NULL;
	map_letter = 'A';
	row = 0;
	split = ft_strsplit(buff, '\n');
	if (split == NULL)
		error_print();
	while (split[row] != NULL)
	{
		tetr_create(&head, split, map_letter, &row);
		map_letter++;
	}
	del_arr(split);
	return (head);
}

/*
 * This function allocates memory and copies the arrays of tetrimino
 * in the struct and assigns the correct letter starting from 'A' to
 * to the tetrimino.
*/
void	tetr_create(t_tetlist **head, char **split, char map_sym, int *row)
{
	t_tetlist	*tetr;
	int			count;

	tetr = NULL;
	count = 0;
	tetr = (t_tetlist *)malloc(sizeof(t_tetlist));
	tetr->map = (char **)malloc((4 + 1) * sizeof(char *));
	tetr->map[4] = NULL;
	while (count < 4)
	{
		tetr->map[count] = ft_strnew(4);
		if (tetr->map[count] == NULL)
			del_arr(tetr->map);
		ft_strcpy(tetr->map[count], split[*row]);
		*row = *row + 1;
		count++;
	}
	tetr->symbol = map_sym;
	tetr_link(head, tetr);
}

/*
 * This function links the created tetriminoes in a linked list.
*/
void	tetr_link(t_tetlist **head, t_tetlist *tetr)
{
	t_tetlist	*start;

	start = *head;
	if (*head == NULL)
		*head = tetr;
	else
	{
		while (start->next != NULL)
			start = start->next;
		start->next = tetr;
	}
}

/*
 * Tetr_move function moves the tetrimino to the top-left position.
*/
void	tetr_move(char **map, int *x_min, int *y_min, int x)
{
	int	y;

	y = 0;
	while (y < 4)
	{
		while (x < 4)
		{
			if (map[y][x] == '#')
			{
				if (*y_min == 0 && *x_min == 0)
					break ;
				map[y - *y_min][x - *x_min] = '#';
				map[y][x] = '.';
			}
			x++;
		}
		x = 0;
		y++;
	}
	*x_min = 5;
	*y_min = 5;
}

/*
 * Function that saves the coordinates of the tetrimino in struct element
 * y_pos and x_pos.
*/
void	save_coord(t_tetlist *head, int x, int y)
{
	int	i;

	i = 0;
	while (y < 4)
	{
		while (x < 4)
		{
			if (head->map[y][x] == '#')
			{
				head->x_pos[i] = x;
				head->y_pos[i] = y;
				i++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
