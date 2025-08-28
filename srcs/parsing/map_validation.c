/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:55:10 by bleow             #+#    #+#             */
/*   Updated: 2025/08/28 21:59:39 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		is_valid_path(t_game *game, int y, int x);
char	**copy_map_array(char **source_map, int rows);
int		flood_fill_validate(t_game *game, char **test_map, int y, int x);
int		is_reachable_space(char c);
int		validate_map_boundaries(char **map, int rows);

/*
Path validation using flood fill algorithm.
Ensures the entire reachable area is properly enclosed by walls.
Returns 1 if valid (enclosed playable area), 0 if invalid (map leakage).
Uses test_map for marking visited tiles
*/
int	is_valid_path(t_game *game, int y, int x)
{
	char	**test_map;
	int		result;

	test_map = copy_map_array(game->map.map, game->map.max_rows);
	if (!test_map)
		return (0);
	if (validate_map_boundaries(test_map, game->map.max_rows) == 0)
	{
		ft_fprintf(2, "Error: Map boundaries must be enclosed by '1' or ' '\n");
		ft_free_2d(test_map, game->map.max_rows);
		return (0);
	}
	result = flood_fill_validate(game, test_map, y, x);
	ft_free_2d(test_map, game->map.max_rows);
	if (result)
		ft_fprintf(2, "All reachable areas are enclosed by walls\n");
	else
	{
		ft_fprintf(2, "FAILURE: Map validation failed\n");
		ft_fprintf(2, "Player can reach map edges\n");
	}
	return (result);
}

/*
Create a deep copy of a 2D map array for validation.
*/
char	**copy_map_array(char **source_map, int rows)
{
	char	**copy;
	int		i;

	if (!source_map || rows <= 0)
	{
		ft_fprintf(2, "Copy_map_array: invalid source_map or rows\n");
		return (NULL);
	}
	copy = (char **)malloc(sizeof(char *) * (rows));
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
	return (copy);
}

/*
Flood fill algorithm with boundary validation using test_map for marking.
Recursively marks reachable spaces and validates enclosure.
Uses 'X' character in test_map to mark visited tiles.
*/
int	flood_fill_validate(t_game *game, char **test_map, int y, int x)
{
	if (y < 0 || y >= game->map.max_rows || x < 0 || x >= game->map.max_cols)
	{
		ft_fprintf(2, "flood_fill_validate: out of bounds at (%d, %d)\n", y, x);
		return (0);
	}
	if (test_map[y][x] == 'X')
		return (1);
	if (game->map.map[y][x] == '1' || game->map.map[y][x] == ' ')
		return (1);
	if (!is_reachable_space(game->map.map[y][x]))
		return (0);
	test_map[y][x] = 'X';
	if (y == 0 || y == game->map.max_rows - 1 || x == 0
		|| x == game->map.max_cols - 1)
	{
		ft_fprintf(2, "Error: Reachable space at map edge (%d,%d)\n", y, x);
		return (0);
	}
	if ((!flood_fill_validate(game, test_map, y - 1, x))
		|| (!flood_fill_validate(game, test_map, y + 1, x))
		|| (!flood_fill_validate(game, test_map, y, x - 1))
		|| (!flood_fill_validate(game, test_map, y, x + 1)))
		return (0);
	return (1);
}

/*
Check if character represents a reachable space.
*/
int	is_reachable_space(char c)
{
	return (c == '0' || c == 'D' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

/*
Controller function to validate map boundaries.
*/
int	validate_map_boundaries(char **map, int rows)
{
	int	r;
	int	max_col;

	max_col = get_max_col(map, rows);
	if (!chk_top_boundary(map[0]))
		return (0);
	if (!chk_bottom_boundary(map[rows - 1]))
		return (0);
	r = 0;
	while (r < rows)
	{
		if (!chk_row_boundary(map[r], max_col))
			return (0);
		r++;
	}
	return (1);
}
