/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:55:10 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 17:43:34 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int		is_valid_path(t_game *game, int y, int x);
int		flood_fill_validate(t_game *game, int y, int x);
int		is_reachable_space(char c);

/*
Path validation using flood fill algorithm.
Ensures the entire reachable area is properly enclosed by walls.
Returns 1 if valid (enclosed playable area), 0 if invalid (map leakage).
Uses test_map for marking visited tiles - much more efficient than separate allocation.
*/
int	is_valid_path(t_game *game, int y, int x)
{
	int		result;

	fprintf(stderr, "DEBUG: Starting enhanced path validation from (%d,%d)\n", y, x);
	fprintf(stderr, "DEBUG: Map dimensions: %dx%d\n", game->map.max_cols, game->map.max_rows);
	fprintf(stderr, "DEBUG: Using test_map for flood fill marking\n");
	
	// Ensure test_map exists as a copy of the main map
	if (create_test_map(game) != 0)
	{
		ft_fprintf(2, "ERROR: Failed to create test_map for flood fill validation\n");
		return (0);
	}
	
	result = flood_fill_validate(game, y, x);
	fprintf(stderr, "DEBUG: Flood fill validation result: %d\n", result);
	
	if (result)
	{
		ft_fprintf(1, "SUCCESS: Map validation passed\n");
		ft_fprintf(1, "All reachable areas are properly enclosed by walls\n");
	}
	else
	{
		ft_fprintf(2, "FAILURE: Map validation failed\n");
		ft_fprintf(2, "Player can reach map edges\n");
	}
	return (result);
}

/*
Flood fill algorithm with boundary validation using test_map for marking.
Recursively marks reachable spaces and validates enclosure.
Uses 'X' character in test_map to mark visited tiles.
*/
int	flood_fill_validate(t_game *game, int y, int x)
{
	char	map_char;

	if (y >= 0 && y < game->map.max_rows && x >= 0 && x < game->map.max_cols)
		map_char = game->map.map[y][x];
	else
		map_char = '?';
	fprintf(stderr, "DEBUG: Checking position (%d,%d), char='%c'\n", y, x, map_char);
	
	if (y < 0 || y >= game->map.max_rows || x < 0 || x >= game->map.max_cols)
	{
		fprintf(stderr, "DEBUG: Out of bounds at (%d,%d)\n", y, x);
		return (0);
	}
	
	if (game->map.test_map[y][x] == 'X')
	{
		fprintf(stderr, "DEBUG: Already visited (%d,%d)\n", y, x);
		return (1);
	}
	
	if (game->map.map[y][x] == '1')
	{
		fprintf(stderr, "DEBUG: Found wall at (%d,%d)\n", y, x);
		return (1);
	}
	
	if (!is_reachable_space(game->map.map[y][x]))
	{
		fprintf(stderr, "DEBUG: Invalid space '%c' at (%d,%d)\n", game->map.map[y][x], y, x);
		return (0);
	}
	
	game->map.test_map[y][x] = 'X';
	fprintf(stderr, "DEBUG: Marked (%d,%d) as visited in test_map\n", y, x);
	
	if (y == 0 || y == game->map.max_rows - 1
		|| x == 0 || x == game->map.max_cols - 1)
	{
		ft_fprintf(2, "Error: Reachable space at map edge (%d,%d)\n", y, x);
		return (0);
	}
	
	if (!flood_fill_validate(game, y - 1, x)
		|| !flood_fill_validate(game, y + 1, x)
		|| !flood_fill_validate(game, y, x - 1)
		|| !flood_fill_validate(game, y, x + 1))
	{
		fprintf(stderr, "DEBUG: Validation failed from (%d,%d)\n", y, x);
		return (0);
	}
	fprintf(stderr, "DEBUG: Successfully validated (%d,%d)\n", y, x);
	return (1);
}

/*
Check if character represents a reachable space.
*/
int	is_reachable_space(char c)
{
	return (c == '0' || c == 'H' || c == 'V' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}
