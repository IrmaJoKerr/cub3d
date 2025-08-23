/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:00:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 00:28:35 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		calc_map_area(int fd, t_game *game, int i);
int		validate_map_line_chars(const char *line);
int		validate_border_line(const char *line);
int		populate_map_array(const char *file, t_game *game, int map_start_line);
void	count_player_chars(const char *line, t_game *game);
int		validate_interior_line(const char *line);
int		parse_map_section(const char *file, t_game *game, int map_start_line);
void	find_player_position(t_game *game);
int		final_map_validation(t_game *game);

/*
Calculate map dimensions and validate map characters
Starting from map_start_line, read until EOF
*/
int	calc_map_area(int fd, t_game *game, int i)
{
	char	*line;
	int		player_found;

	player_found = 0;
	while ((i <= map_end_line) && (line != NULL))
	{
		line = get_next_line(fd);
		if (ft_strlen(line) > game->map.max_cols)
			game->map.max_cols = ft_strlen(line);
		if (!validate_map_line_chars(line, game, game->map.max_rows,
				&player_found))
		{
			free(line);
			return (-1);
		}
		free(line);
		game->map.max_rows++;
		i++;
	}
	if (game->map.herocount != 1)
		return (-1);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (!is_only_whitespace(line))
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

/*
Set hero/player start position and direction
*/
void	set_hero_start(t_game *game, char dir)
{
	if (dir == 'N')
		game->map.start_direction = N;
	else if (dir == 'E')
		game->map.start_direction = E;
	else if (dir == 'S')
		game->map.start_direction = S;
	else if (dir == 'W')
		game->map.start_direction = W;
}

/**
 * Validate map line contains only valid characters
 */

int	validate_map_line_chars(const char *line, t_game *game, int row,
		int *player_found)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(VALID_CHARS " ", line[i]))
			return (-1);
		if (line[i] == 'D')
			game->doorcount++;
		if (ft_strchr("NSEW", line[i]))
		{
			game->map.herocount++;
			if (!(*player_found))
			{
				game->map.player_x = i;
				game->map.player_y = row;
				set_hero_start(game, line[i]);
				*player_found = 1;
			}
		}
		i++;
	}
	return (0);
}

/*
Validate border line (first/last) contains only 1's and spaces
*/
int	validate_border_line(const char *line)
{
	int	i;
	int	has_wall;

	i = 0;
	has_wall = 0;
	while (line[i])
	{
		if (line[i] == '1')
			has_wall = 1;
		else if (line[i] != ' ')
			return (0);
		i++;
	}
	return (has_wall);
}

/*
Allocate and populate 2D map array
*/
int	populate_map_array(const char *file, t_game *game, int map_start_line)
{
	int		fd;
	char	*line;
	int		line_num;
	int		map_row;
	int		len;
	char	*last_line;

	game->map.map = (char **)malloc(sizeof(char *) * (game->map.max_rows + 1));
	if (!game->map.map)
	{
		ft_fprintf(2, "Error: Failed to allocate memory for map\n");
		return (-1);
	}
	
	// Initialize all pointers to NULL for safety
	ft_memset(game->map.map, 0, sizeof(char *) * (game->map.max_rows + 1));
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(game->map.map);
		game->map.map = NULL;
		return (-1);
	}
	line_num = 0;
	map_row = 0;
	while (line_num < map_start_line)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
		line_num++;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		
		// Skip empty lines and whitespace-only lines but continue reading
		if (ft_strlen(line) == 0 || is_only_whitespace(line))
		{
			free(line);
			continue;
		}
		
		// Stop when we have enough rows
		if (map_row >= game->map.max_rows)
		{
			free(line);
			break;
		}
		// Allocate memory for the row using max_cols for uniform sizing
		game->map.map[map_row] = (char *)malloc(game->map.max_cols + 1);
		if (!game->map.map[map_row])
		{
			ft_fprintf(2, "Error: Failed to allocate memory for map line\n");
			free(line);
			close(fd);
			return (-1);
		}
		
		// Initialize entire row with space characters for void areas
		ft_memset(game->map.map[map_row], ' ', game->map.max_cols);
		
		// Set uniform null terminator at the end of allocated space
		game->map.map[map_row][game->map.max_cols] = '\0';
		
		// Selective character-by-character copying - only copy non-space characters
		int i = 0;
		int line_len = ft_strlen(line);
		
		// Debug: Print line length information
		ft_fprintf(2, "Row %d: line_len=%d, max_cols=%d\n", map_row, line_len, game->map.max_cols);
		
		while (i < line_len && i < game->map.max_cols)
		{
			// Copy all characters including spaces
			game->map.map[map_row][i] = line[i];
			i++;
		}
		// Remaining positions keep their space values from memset (void padding)
		count_player_chars(line, game);
		if (map_row > 0 && map_row < game->map.max_rows - 1)
		{
			// Temporarily disable strict interior validation for irregular maps
			// if (!validate_interior_line(line))
			// {
			// 	ft_fprintf(2, "Error: \n");
			// 	ft_fprintf(2, "Interior map must start and end with walls\n");
			// 	free(line);
			// 	close(fd);
			// 	return (-1);
			// }
		}
		free(line);
		map_row++;
	}
	if (map_row > 0)
	{
		last_line = game->map.map[map_row - 1];
		if (validate_border_line(last_line))
		{
			// game->map.map_last_wall = true;      // OBSOLETE FIELD
		}
		else
		{
			// Temporarily disable for debugging irregular maps
			// ft_fprintf(2, "Error: Last map line must contain only walls and spaces\n");
			// close(fd);
			// return (-1);
			// game->map.map_last_wall = false;    // OBSOLETE FIELD
		}
	}
	game->map.map[map_row] = NULL;
	close(fd);
	return (0);
}

/*
 * DEPRECATED: Count player characters in line
 * Logic now handled in validate_map_line_chars()
 */
// void	count_player_chars(const char *line, t_game *game)
// {
//     int	i;
//
//     i = 0;
//     while (line[i])
//     {
//         if (ft_strchr("NSEW", line[i]))
//             game->map.herocount++;
//         i++;
//     }
// }

/*
Validate interior line starts and ends with walls
*/
int	validate_interior_line(const char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len < 2)
		return (0);
	return (line[0] == '1' && line[len - 1] == '1');
}

/**
 * Parse map section (second pass)
 * Returns 0 on success, -1 on error
 */
int	parse_map_section(const char *file, t_game *game, int map_start_line)
{
	// First: Calculate dimensions and validate characters
	if (calculate_map_dimensions(file, game, map_start_line) < 0)
		return (-1);
	ft_fprintf(2, "Map dimensions: %dx%d\n", game->map.max_cols, game->map.max_rows);
	// Second: Allocate and populate map array
	if (populate_map_array(file, game, map_start_line) < 0)
		return (-1);
	// Third: Find player position
	find_player_position(game);
	// Debug: Print map contents for verification
	debug_print_map(game);
	// Fourth: Final validation
	if (final_map_validation(game) < 0)
		return (-1);
	ft_fprintf(2, "Map parsing completed successfully\n");
	return (0);
}

/**
 * Find player starting position
 */
void	find_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.max_rows)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.map[y]))
		{
			if (ft_strchr("NSEW", game->map.map[y][x]))
			{
				game->map.player_x = x;
				game->map.player_y = y;
				game->curr_x = x;
				game->curr_y = y;
				if (game->map.map[y][x] == 'N')
					game->map.start_direction = N;
				else if (game->map.map[y][x] == 'E')
					game->map.start_direction = E;
				else if (game->map.map[y][x] == 'S')
					game->map.start_direction = S;
				else if (game->map.map[y][x] == 'W')
					game->map.start_direction = W;
				return ;
			}
			x++;
		}
		y++;
	}
}

/**
 * Final map validation
 */
int	final_map_validation(t_game *game)
{
	if (game->map.herocount != 1)
	{
		ft_fprintf(2, "Error: Map must have exactly one player (found %d)\n", game->map.herocount);
		return (-1);
	}
	// if (!game->map.map_first_wall)           // OBSOLETE FIELD - validation disabled
	// {
	//	ft_fprintf(2, "Error: First map line must be all walls\n");
	//	return (-1);
	// }
	// Temporarily disable last wall validation for irregular maps
	// if (!game->map.map_last_wall)
	// {
	// 	ft_fprintf(2, "Error: Last map line must be all walls\n");
	// 	return (-1);
	// }
	if (!is_valid_path(game, game->map.player_y, game->map.player_x))
	{
		ft_fprintf(2, "Error: Player has no valid path\n");
		return (-1);
	}
	return (0);
}
