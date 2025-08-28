/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:54:36 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 20:06:58 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		get_max_col(char **map, int rows);
int		chk_top_boundary(char *row);
int		chk_bottom_boundary(char *row);
int		chk_row_boundary(char *row, int max_col);

/*
Get the maximum column length from the map.
*/
int	get_max_col(char **map, int rows)
{
	int	r;
	int	len;
	int	max_col;

	max_col = 0;
	r = 0;
	while (r < rows)
	{
		len = 0;
		while (map[r][len])
			len++;
		if (len > max_col)
			max_col = len;
		r++;
	}
	return (max_col);
}

/*
Check if the top boundary row is valid (only '1' or ' ').
*/
int	chk_top_boundary(char *row)
{
	int	c;

	c = 0;
	while (row[c])
	{
		if (row[c] != ' ' && row[c] != '1')
			return (0);
		c++;
	}
	return (1);
}

/*
Check if the bottom boundary row is valid (only '1' or ' ').
*/
int	chk_bottom_boundary(char *row)
{
	int	c;

	c = 0;
	while (row[c])
	{
		if (row[c] != ' ' && row[c] != '1')
			return (0);
		c++;
	}
	return (1);
}

/*
Check if a row has valid boundaries (starts and ends with '1' ignoring spaces).
*/
int	chk_row_boundary(char *row, int max_col)
{
	int	len;
	int	left;
	int	right;

	len = 0;
	while (row[len])
		len++;
	left = 0;
	while (left < len && row[left] == ' ')
		left++;
	if (left == len || row[left] != '1')
		return (0);
	right = len - 1;
	while (right >= 0 && row[right] == ' ')
		right--;
	if (right < 0 || row[right] != '1')
		return (0);
	if (len < max_col)
	{
		if (!(row[left] == '1' && row[right] == '1'))
			return (0);
	}
	return (1);
}
