/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:55:10 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 17:43:53 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int	is_valid_path(t_game *game, int y, int x);
int	flood_fill_validate(t_game *game, char **test_map, int y, int x);
int	is_reachable_space(char c);

/*
Path validation using flood fill algorithm.
Ensures the entire reachable area is properly enclosed by walls.
Returns 1 if valid (enclosed playable area), 0 if invalid (map leakage).
Uses test_map for marking visited tiles - much more efficient than separate allocation.
*/
int	is_valid_path(t_game *game, int y, int x)
{
	char	**test_map;
	int		result;

	fprintf(stderr, "DEBUG: Starting enhanced path validation from (%d,%d)\n", y, x);
	fprintf(stderr, "DEBUG: Map dimensions: %dx%d\n", game->map.max_cols, game->map.max_rows);
	fprintf(stderr, "DEBUG: Using local test_map for flood fill marking\n");
	test_map = copy_map_array(game->map.map, game->map.max_rows);
	if (!test_map)
	{
		fprintf(stderr, "ERROR: Failed to allocate local test_map for flood fill validation\n");
		return (0);
	}
	result = flood_fill_validate(game, test_map, y, x);
	fprintf(stderr, "DEBUG: Flood fill validation result: %d\n", result);
	ft_free_2d(test_map, game->map.max_rows);
	if (result)
	{
		fprintf(stdout, "SUCCESS: Map validation passed\n");
		fprintf(stdout, "All reachable areas are properly enclosed by walls\n");
	}
	else
	{
		fprintf(stderr, "FAILURE: Map validation failed\n");
		fprintf(stderr, "Player can reach map edges\n");
	}
	return (result);
}

/*
Flood fill algorithm with boundary validation using test_map for marking.
Recursively marks reachable spaces and validates enclosure.
Uses 'X' character in test_map to mark visited tiles.
*/
int	flood_fill_validate(t_game *game, char **test_map, int y, int x)
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
	if (test_map[y][x] == 'X')
	{
		fprintf(stderr, "DEBUG: Already visited (%d,%d)\n", y, x);
		return (1);
	}
	if (game->map.map[y][x] == '1' || game->map.map[y][x] == ' ')
	{
		fprintf(stderr, "DEBUG: Found wall/void at (%d,%d), char='%c'\n", y, x, game->map.map[y][x]);
		return (1);
	}
	if (!is_reachable_space(game->map.map[y][x]))
	{
		fprintf(stderr, "DEBUG: Invalid space '%c' at (%d,%d)\n", game->map.map[y][x], y, x);
		return (0);
	}
	test_map[y][x] = 'X';
	fprintf(stderr, "DEBUG: Marked (%d,%d) as visited in test_map\n", y, x);
	if (y == 0 || y == game->map.max_rows - 1
		|| x == 0 || x == game->map.max_cols - 1)
	{
		fprintf(stderr, "Error: Reachable space at map edge (%d,%d)\n", y, x);
		return (0);
	}
	if (!flood_fill_validate(game, test_map, y - 1, x)
		|| !flood_fill_validate(game, test_map, y + 1, x)
		|| !flood_fill_validate(game, test_map, y, x - 1)
		|| !flood_fill_validate(game, test_map, y, x + 1))
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
	return (c == '0' || c == 'D' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

/*
Additional debug function to validate the entire map line by line.
Logs detailed information about each line's validation result.
*/
void	validate_map_lines(t_game *game)
{
	int	line;
	int	result;

	line = 0;
	while (line < game->map.max_rows)
	{
		fprintf(stderr, "[DEBUG] Validating map line: %s\n", game->map.map[line]);
		result = is_valid_path(game, line, 0);
		if (result)
			fprintf(stderr, "[DEBUG] Map line %d is valid\n", line);
		else
			fprintf(stderr, "[DEBUG] Map line %d is invalid\n", line);
		line++;
	}
}
