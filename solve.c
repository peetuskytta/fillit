/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:06:28 by igaplich          #+#    #+#             */
/*   Updated: 2022/03/01 13:02:49 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * This function calls other functions in order to find the smallest
 * possible square of the tetriminoes given. First it checks
*/
char	**solver(t_tetlist *head, int pieces)
{
	int			size;
	char		**fill_map;

	size = map_minsize(pieces);
	fill_map = map_create(size);
	while (fillit_algo(head, pieces, size, fill_map) == 0)
	{
		del_arr(fill_map);
		size++;
		fill_map = map_create(size);
	}
	return (fill_map);
}

/*
 * This function uses recursion to find the correct place for each
 * tetrimino.
 */
int	fillit_algo(t_tetlist *tetr, int pieces, int size, char **fill_map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (tetr == NULL)
		return (1);
	while (y < size)
	{
		while (x < size)
		{
			if (inserting_tetr(fill_map, tetr, x, y) == 1)
			{
				if (fillit_algo(tetr->next, pieces, size, fill_map) == 0)
					del_tetr(tetr, fill_map);
				else
					return (1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

/*
 * Allocating memory for the tetrimino map and setting all positions
 * to '.' (dots).
*/
char	**map_create(int size)
{
	char	**fill_map;
	int		i;

	i = 0;
	fill_map = (char **)malloc((size + 1) * sizeof(char *));
	if (!fill_map)
		error_print();
	while (i < size)
	{
		fill_map[i] = ft_strnew(size);
		if (!fill_map[i])
			del_arr(fill_map);
		ft_memset(fill_map[i], '.', size);
		i++;
	}
	fill_map[size] = NULL;
	return (fill_map);
}

/*
 * Function to rewrite data on fill_map back to '.' when
 * tetrimino doesn't to fit on the map.
*/
void	del_tetr(t_tetlist *tetr, char **fill_map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		fill_map[tetr->y_map[i]][tetr->x_map[i]] = '.';
		i++;
	}
}

/*
 * Function which tries to insert tetrimino on the map. 
 * Returns 1 if successful 0 if not.
*/
int	inserting_tetr(char **solution, t_tetlist *tetr, int x, int y)
{
	int		i;
	int		len;

	len = (int)ft_strlen(solution[0]);
	i = 0;
	while (i < 4)
	{
		if (y + tetr->y_pos[i] < len && x + tetr->x_pos[i] < len)
		{
			if (solution[y + tetr->y_pos[i]][x + tetr->x_pos[i]] == '.')
				i++;
			else
				return (0);
		}
		else
			return (0);
	}
	i = -1;
	while (++i < 4)
	{
		solution[y + tetr->y_pos[i]][x + tetr->x_pos[i]] = tetr->symbol;
		tetr->x_map[i] = x + tetr->x_pos[i];
		tetr->y_map[i] = y + tetr->y_pos[i];
	}
	return (1);
}
