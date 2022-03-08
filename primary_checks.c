/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:06:36 by igaplich          #+#    #+#             */
/*   Updated: 2022/03/01 13:12:03 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
 * This function checks that the number of '#' is equal to 4 in every
 * tetrimino. It returns the number of total '#' found in buffer. In
 * case of errors it uses error_print function to exit.
*/

int	symb_amount_check(char *buff, int hash_c, int i, int tetr_last)
{
	int	total_hash;

	total_hash = 0;
	while (buff[i] != '\0')
	{
		while (buff[i] != '\0' && i < tetr_last)
		{
			if (buff[i] == '#')
			{
				hash_c++;
				total_hash++;
			}
			i++;
		}
		if (hash_c != 4)
			error_print();
		tetr_last += 21;
		hash_c = 0;
	}
	return (total_hash);
}

/*
 * Reads the file containing tetrominoes. Exits if it can't open 
 * or read the file given as an argument.
*/
void	reading_file(char *buff, char **argv)
{
	int	fd;
	int	bytes_read;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_print();
	bytes_read = read(fd, buff, 550);
	if (bytes_read < 20 || bytes_read > 546)
		error_print();
	buff[bytes_read] = '\0';
	if (close(fd) == -1)
		error_print();
}

/*
 * Checking the length of lines and any invalid characters.
 * If check fails at any point exits through error_print function.
*/
void	line_len_check(char *buff, int len_count, int row_count, size_t i)
{
	if (buff[i - 1] == '\n' && buff[i - 2] == '\n')
		error_print();
	while (*buff != '\0')
	{
		while (*buff != '\n' && *buff != '\0')
		{
			if (*buff != '.' && *buff != '#' && *buff != '\n')
				error_print();
			len_count++;
			buff++;
		}
		if (len_count != 4 && row_count % 5 != 0)
			error_print();
		if (row_count % 5 == 0 && len_count != 0)
			error_print();
		row_count++;
		len_count = 0;
		buff++;
	}
}

/*
 * Checking the tetromino shapes are valid based on the amount 
 * of surrounding pieces.
*/
void	shape_check(char *buff, int i, int bonds, int piece)
{
	while (buff[i] != 0)
	{
		if (buff[i] == '#')
		{
			if (buff[i + 1] == '#' && i + 1 < piece)
				bonds++;
			if (buff[i + 5] == '#' && i + 5 < piece)
				bonds++;
		}
		i++;
		if (i == piece && (bonds != 4 && bonds != 3))
			error_print();
		else if (i == piece)
		{
			piece += 21;
			bonds = 0;
		}
		if (buff[i] == '\0' && (bonds != 3 && bonds != 4))
			error_print();
	}
}

/*
 * Function to call all the validity checking functions one
 * at a time. Returns the amount of '#' found.
*/
int	primary_checks(int argc, char **argv, char *buff)
{
	int	symb_amount;

	arg_amount_check(argc);
	reading_file(buff, argv);
	symb_amount = symb_amount_check(buff, 0, 0, 21);
	line_len_check(buff, 0, 1, ft_strlen(buff));
	shape_check(buff, 0, 0, 21);
	return (symb_amount);
}
