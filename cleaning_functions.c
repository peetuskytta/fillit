/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:37:51 by igaplich          #+#    #+#             */
/*   Updated: 2022/03/01 13:04:12 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * Function to free the allocated memory address and setting it to NULL.
*/
void	del_arr(char **to_clean)
{
	int	i;

	i = 0;
	while (to_clean[i] != NULL)
	{
		ft_strdel(&to_clean[i]);
		i++;
	}
	free(to_clean);
	to_clean = NULL;
}

/*
 * Function that frees the memory allocated for the tetrimino struct.
*/
void	del_list(t_tetlist *head)
{
	t_tetlist	*tmp;

	tmp = head;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		del_arr(tmp->map);
		free(tmp);
	}
}
