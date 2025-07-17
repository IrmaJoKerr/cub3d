/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 16:23:19 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Create a deep copy of a 2D map array.
Returns allocated copy on success, NULL on failure.
Caller responsible for cleanup using ft_free_2d().
*/
char	**copy_map_array(char **source_map, int rows)
{
	char	**copy;
	int		i;

	if (!source_map || rows <= 0)
		return (NULL);
	copy = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows && source_map[i])
	{
		copy[i] = ft_strdup(source_map[i]);
		if (!copy[i])
		{
			ft_free_2d(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/*
Create test_map as a copy of the main map.
Safe function that handles allocation failures gracefully.
*/
int	create_test_map(t_game *game)
{
	if (!game->map.map)
	{
		ft_fprintf(2, "Error: Cannot create test_map - main map is NULL\n");
		return (-1);
	}
	if (game->map.test_map)
	{
		fprintf(stderr, "DEBUG: test_map already exists, skipping creation\n");
		return (0);
	}
	game->map.test_map = copy_map_array(game->map.map, game->map.max_rows);
	if (!game->map.test_map)
	{
		ft_fprintf(2, "Warning: Failed to create test_map copy\n");
		return (-1);
	}
	fprintf(stderr, "DEBUG: Successfully created test_map copy (%dx%d)\n", 
		game->map.max_cols, game->map.max_rows);
	return (0);
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
