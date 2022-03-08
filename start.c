/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 14:40:55 by igaplich          #+#    #+#             */
/*   Updated: 2022/03/01 17:49:13 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Checking the number of arguments.
*/
void	arg_amount_check(int argc)
{
	if (argc != 2)
	{
		ft_putstr("usage: ./fillit _map_name_");
		ft_putchar('\n');
		exit (1);
	}
}

/*
 * Exit function for error cases. exit(1) means exit with error.
*/
void	error_print(void)
{
	ft_putendl("error");
	exit (1);
}

/*
 * Function which returns the minimum size for the map based on the number
 * of tetriminoes given.
*/
int	map_minsize(int pieces)
{
	int	hashes;
	int	min_size;

	min_size = 2;
	hashes = pieces * 4;
	while ((min_size * min_size) < hashes)
		min_size++;
	return (min_size);
}

/*
 * Function to manipulate the tetriminoes for later use. Saving coordinates
 * and repositioning of them.
*/
void	tetr_manipulation(t_tetlist *head, int x_min, int y_min, int x)
{
	int	y;

	while (head != NULL)
	{
		y = 0;
		while (y < 4)
		{
			while (x < 4)
			{
				if (head->map[y][x] == '#')
				{
					if (y < y_min)
						y_min = y;
					if (x < x_min)
						x_min = x;
				}
				x++;
			}
			x = 0;
			y++;
		}
		tetr_move(head->map, &x_min, &y_min, 0);
		save_coord(head, 0, 0);
		head = head->next;
	}
}

/*
 * The driver function of this program. Calls all the necessary
 * functions in order to return a solution and printing it to
 * standard output.
*/
int	main(int argc, char **argv)
{
	char		buff[550];
	t_tetlist	*head;
	char		**solution;
	int			hash_count;
	int			i;

	i = 0;
	hash_count = primary_checks(argc, argv, buff);
	head = tetr_split(buff);
	tetr_manipulation(head, 5, 5, 0);
	solution = solver(head, hash_count / 4);
	while (solution[i] != NULL)
	{
		ft_putstr(solution[i]);
		ft_putchar('\n');
		i++;
	}
	del_arr(solution);
	del_list(head);
	return (0);
}
