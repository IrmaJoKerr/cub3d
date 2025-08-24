/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:00:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 18:22:24 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		calc_map_area(int fd, t_game *game, int i);
int		validate_border_line(const char *line);

int		validate_interior_line(const char *line);
// int		parse_map_section(const char *file, t_game *game, int map_start_line);
// void	find_player_position(t_game *game);
int		final_map_validation(t_game *game);
int		strip_newline(char *line);

/*
Calculate map dimensions and validate map characters
Starting from map_start_line, read until EOF
*/
int	calc_map_area(int fd, t_game *game, int i)
{
	char	*line;
	int		player_found;

	player_found = 0;
	line = NULL;
	while ((i < game->map.map_last_line))
	{
		line = get_next_line(fd);
		if (!line) break;
		if ((int)ft_strlen(line) > game->map.max_cols)
		{
			game->map.max_cols = (int)ft_strlen(line);
		}
		if (validate_map_line_chars(line, game, game->map.max_rows, &player_found) < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
		game->map.max_rows++;
		i++;
	}
	if (game->map.herocount != 1)
	{
		return (-1);
	}
	return (0);
}

/*
Set hero/player start position and direction
*/
void	set_hero_start(t_game *game, char dir)
{
	game->curr_x = game->map.player_x + 0.5;
	game->curr_y = game->map.player_y + 0.5;
	game->view_elevation = 0.0;
	if (dir == 'N')
	{
		game->map.start_direction = N;
		game->view_direction = 3 * M_PI / 2;
	}
	else if (dir == 'E')
	{
		game->map.start_direction = E;
		game->view_direction = 0;
	}
	else if (dir == 'S')
	{
		game->map.start_direction = S;
		game->view_direction = M_PI / 2;
	}
	else if (dir == 'W')
	{
		game->map.start_direction = W;
		game->view_direction = M_PI;
	}
}

/*
Validate map line contains only valid characters
*/
int	validate_map_line_chars(const char *line, t_game *game, int row,
		int *player_found)
{
	char	*mutable_line;
	int		i;

	mutable_line = ft_strdup(line);
	if (!mutable_line)
	{
		return (-1);
	}
	strip_newline(mutable_line);

	i = 0;
	while (mutable_line[i])
	{
		if (!ft_strchr(VALID_CHARS " ", mutable_line[i]))
		{
			free(mutable_line);
			return (-1);
		}
		if (mutable_line[i] == 'D')
		{
			game->doorcount++;
		}
		if (ft_strchr("NSEW", mutable_line[i]))
		{
			game->map.herocount++;
			if (!(*player_found))
			{
				game->map.player_x = i;
				game->map.player_y = row;
				set_hero_start(game, mutable_line[i]);
				*player_found = 1;
			}
		}
		i++;
	}
	free(mutable_line);
	return (0);
}

int strip_newline(char *line)
{
    int len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
        return (1);
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

// /*
// Parse map section (second pass)
// Returns 0 on success, -1 on error
// */
// int	parse_map_section(const char *file, t_game *game, int map_start_line)
// {
// 	// First: Calculate dimensions and validate characters
// 	if (calc_map_area(open(file, O_RDONLY), game, map_start_line) < 0)
// 		return (-1);
// 	ft_fprintf(2, "Map dimensions: %dx%d\n", game->map.max_cols, game->map.max_rows);
// 	// Second: Allocate and populate map array
// 	if (populate_map_array(file, game, map_start_line) < 0)
// 		return (-1);
// 	// Third: Find player position
// 	find_player_position(game);
// 	// Debug: Print map contents for verification
// 	debug_print_map(game);
// 	// Fourth: Final validation
// 	if (final_map_validation(game) < 0)
// 		return (-1);
// 	ft_fprintf(2, "Map parsing completed successfully\n");
// 	return (0);
// }

// /*
// Find player starting position
// */
// void	find_player_position(t_game *game)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (y < game->map.max_rows)
// 	{
// 		x = 0;
// 		while (x < (int)ft_strlen(game->map.map[y]))
// 		{
// 			if (ft_strchr("NSEW", game->map.map[y][x]))
// 			{
// 				game->map.player_x = x;
// 				game->map.player_y = y;
// 				game->curr_x = x;
// 				game->curr_y = y;
// 				if (game->map.map[y][x] == 'N')
// 					game->map.start_direction = N;
// 				else if (game->map.map[y][x] == 'E')
// 					game->map.start_direction = E;
// 				else if (game->map.map[y][x] == 'S')
// 					game->map.start_direction = S;
// 				else if (game->map.map[y][x] == 'W')
// 					game->map.start_direction = W;
// 				return ;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

/*
Final map validation
*/
int	final_map_validation(t_game *game)
{
	if (game->map.herocount != 1)
	{
		fprintf(stderr, "Error: Map must have exactly one player (found %d)\n", game->map.herocount);
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
		fprintf(stderr, "Error: Player has no valid path\n");
		return (-1);
	}
	return (0);
}
