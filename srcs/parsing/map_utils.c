/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/23 13:12:33 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
char	**copy_map_array(char **source_map, int rows);
void	cleanup_single_map(char ***map_ptr);

/*
Create a deep copy of a 2D map array.
Returns allocated copy on success, NULL on failure.
Caller responsible for cleanup using ft_free_2d().
*/
char	**copy_map_array(char **source_map, int rows)
{
	char	**copy;
	int		i;

	fprintf(stderr, "[DEBUG] copy_map_array: source_map=%p, rows=%d\n", (void*)source_map, rows);
	if (!source_map || rows <= 0)
	{
		fprintf(stderr, "[DEBUG] copy_map_array: invalid source_map or rows\n");
		return (NULL);
	}
	copy = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!copy)
	{
		fprintf(stderr, "[DEBUG] copy_map_array: malloc failed for copy\n");
		return (NULL);
	}
	i = 0;
	while (i < rows && source_map[i])
	{
		fprintf(stderr, "[DEBUG] copy_map_array: copying row %d: '%s'\n", i, source_map[i]);
		copy[i] = ft_strdup(source_map[i]);
		if (!copy[i])
		{
			fprintf(stderr, "[DEBUG] copy_map_array: ft_strdup failed for row %d\n", i);
			ft_free_2d(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	fprintf(stderr, "[DEBUG] copy_map_array: successfully copied %d rows\n", i);
	return (copy);
}

/*
Helper function for cleaning up a single map array.
*/
void	cleanup_single_map(char ***map_ptr)
{
	size_t	map_len;

	if (map_ptr && *map_ptr)
	{
		map_len = ft_arrlen(*map_ptr);
		ft_free_2d(*map_ptr, map_len);
		*map_ptr = NULL;
	}
}
