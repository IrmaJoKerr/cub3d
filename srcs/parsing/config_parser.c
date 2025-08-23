/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:00:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 00:37:14 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
// int	parse_configuration_section(const char *file, t_game *game);
int	is_only_whitespace(const char *line);
int	is_map_start_line(const char *line, int *in_map);
int	parse_config_settings(char *line, t_game *game);
int	get_texture_path(char *line, t_game *game, int settings_type);
int	handle_color_settings(char *line, t_game *game, int settings_type);
int	validate_required_config(t_game *game);
int	cleanup_and_return(int fd, char *line, int ret_val);
int	check_duplicate_texture(char *path, t_game *game, int settings_type);
void	set_texture_path(char *path, t_game *game, int settings_type);

// /*
// Parse configuration section (before map starts)
// Returns: map_start_line on success, -1 on error
// */
// int	parse_configuration_section(const char *file, t_game *game)
// {
// 	int		fd;
// 	char	*line;
// 	int		line_num;
// 	int		map_start_line;
// 	int		len;

// 	fprintf(stderr, "[DEBUG] Entering parse_configuration_section for file: %s\n", file);
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		fprintf(stderr, "[DEBUG] Error: Cannot open file %s\n", file);
// 		ft_fprintf(2, "Error: Cannot open file %s\n", file);
// 		return (-1);
// 	}
// 	game->map.map_path = ft_strdup(file);
// 	if (!game->map.map_path)
// 		return (cleanup_and_return(fd, NULL, -1));
// 	line_num = 0;
// 	map_start_line = -1;
// 	line = get_next_line(fd);
// 	while ((line != NULL)
// 	{
// 		line = get_next_line(fd);
// 		len = ft_strlen(line);
// 		if (len > 0 && line[len - 1] == '\n')
// 			line[len - 1] = '\0';
// 		if (ft_strlen(line) == 0 || is_only_whitespace(line))
// 		{
// 			fprintf(stderr, "[DEBUG] Skipping blank/whitespace line %d\n", line_num);
// 			free(line);
// 			line_num++;
// 			continue ;
// 		}
// 		fprintf(stderr, "[DEBUG] Parsing line %d: '%s'\n", line_num, line);
// 		if (is_map_start_line(line))
// 		{
// 			fprintf(stderr, "[DEBUG] Detected map start at line %d: '%s'\n", line_num, line);
// 			map_start_line = line_num;
// 			free(line);
// 			break ;
// 		}
// 		if (parse_config_settings(line, game) < 0)
// 		{
// 			fprintf(stderr, "[DEBUG] Error parsing config settings at line %d: '%s'\n", line_num, line);
// 			return (cleanup_and_return(fd, line, -1));
// 		}
// 		free(line);
// 		line_num++;
// 	}
// 	close(fd);
// 	fprintf(stderr, "[DEBUG] Finished config parsing. Validating required config...\n");
// 	if (validate_required_config(game) < 0)
// 		return (-1);
// 	fprintf(stderr, "[DEBUG] Exiting parse_configuration_section, map_start_line=%d\n", map_start_line);
// 	return (map_start_line);
// }

/*
Check if line contains only whitespace
*/
int	is_only_whitespace(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
Check if line represents the start of map (all 1's and spaces)
*/
int	is_map_start_line(const char *line, int *in_map)
{
	int	i;
	int	has_wall;

	i = 0;
	has_wall = 0;
	while (line[i])
	{
		if (line[i] == '1')
		{
			has_wall = 1;
			*in_map = 1;
		}
		else if (line[i] != ' ')
			return (0);
		i++;
	}
	return (has_wall);
}

/*
Parse individual configuration settings with duplicate checking
*/
int	parse_config_settings(char *line, t_game *game)
{
	int	settings_type;
	int	result;

	result = 0;
	settings_type = identify_settings_type(line);
	if (settings_type >= 1 && settings_type <= 4)
		result = (get_texture_path(line, game, settings_type));
	else if (settings_type == 5 || settings_type == 6)
		result = (handle_color_settings(line, game, settings_type));
	return (result);
}

/*
Get texture path with duplicate checking.
*/
int	get_texture_path(char *line, t_game *game, int settings_type)
{
	char	*path;

	if (settings_type == 1)
		path = extract_texture_path(line, "NO");
	else if (settings_type == 2)
		path = extract_texture_path(line, "SO");
	else if (settings_type == 3)
		path = extract_texture_path(line, "WE");
	else if (settings_type == 4)
		path = extract_texture_path(line, "EA");
	if (!path || !check_valid_texture_path(path))
	{
		ft_fprintf(2, "Error: Invalid texture path");
		if (path)
			free(path);
		return (-1);
	}
	if (!check_duplicate_texture(path, game, settings_type))
		return (-1);
	else
		set_texture_path(path, game, settings_type);
	return (0);
}

int	check_duplicate_texture(char *path, t_game *game, int settings_type)
{
	if (settings_type == 1 && game->map.north_texture_path)
	{
		ft_fprintf(2, "Error: Duplicate NO settings\n");
		free(path);
		return (-1);
	}
	if (settings_type == 2 && game->map.south_texture_path)
	{
		ft_fprintf(2, "Error: Duplicate SO settings\n");
		free(path);
		return (-1);
	}
	if (settings_type == 3 && game->map.west_texture_path)
	{
		ft_fprintf(2, "Error: Duplicate WE settings\n");
		free(path);
		return (-1);
	}
	if (settings_type == 4 && game->map.east_texture_path)
	{
		ft_fprintf(2, "Error: Duplicate EA settings\n");
		free(path);
		return (-1);
	}
	return (0);
}

void	set_texture_path(char *path, t_game *game, int settings_type)
{
	if (path && settings_type == 1)
		game->map.north_texture_path = path;
	else if (path && settings_type == 2)
		game->map.south_texture_path = path;
	else if (settings_type == 3)
		game->map.west_texture_path = path;
	else if (settings_type == 4)
		game->map.east_texture_path = path;
}

/*
Handle color settings with duplicate checking
*/
int	handle_color_settings(char *line, t_game *game, int settings_type)
{
	if ((settings_type == 5) && (game->map.floor_color[0] != -1))
	{
		ft_fprintf(2, "Error: Duplicate F settings\n");
		return (-1);
	}
	else
	{
		parse_floor_color(line, game);
		return (0);
	}
	if ((settings_type == 6) && (game->map.sky_color[0] != -1))
	{
		ft_fprintf(2, "Error: Duplicate C settings\n");
		return (-1);
	}
	else
	{
		parse_ceiling_color(line, game);
		return (0);
	}
}

/*
Validate all required configuration settings are present
*/
int	validate_required_config(t_game *game)
{
	if (!game->map.north_texture_path)
	{
		ft_fprintf(2, "Error: Missing NO (north texture) settings\n");
		return (-1);
	}
	if (!game->map.south_texture_path)
	{
		ft_fprintf(2, "Error: Missing SO (south texture) settings\n");
		return (-1);
	}
	if (!game->map.west_texture_path)
	{
		ft_fprintf(2, "Error: Missing WE (west texture) settings\n");
		return (-1);
	}
	if (!game->map.east_texture_path)
	{
		ft_fprintf(2, "Error: Missing EA (east texture) settings\n");
		return (-1);
	}
	if (game->map.floor_color[0] == -1)
	{
		ft_fprintf(2, "Error: Missing F (floor color) settings\n");
		return (-1);
	}
	if (game->map.sky_color[0] == -1)
	{
		ft_fprintf(2, "Error: Missing C (ceiling color) settings\n");
		return (-1);
	}
	return (0);
}

/**
 * Cleanup and return helper
 */
int	cleanup_and_return(int fd, char *line, int ret_val)
{
	if (line)
		free(line);
	if (fd >= 0)
		close(fd);
	return (ret_val);
}
