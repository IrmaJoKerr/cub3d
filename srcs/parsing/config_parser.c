/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:00:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 17:46:35 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes (in order)
*/
int		is_only_whitespace(const char *line);
int		is_map_start_line(const char *line, int *in_map);
int		parse_config_settings(char *line, t_game *game);
int		get_texture_path(char *line, t_game *game, int settings_type);
int		handle_color_settings(char *line, t_game *game, int settings_type);
int		validate_required_config(t_game *game);
int		cleanup_and_return(int fd, char *line, int ret_val);
int		check_duplicate_texture(char *path, t_game *game, int settings_type);
void	set_texture_path(char *path, t_game *game, int settings_type);


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
		{
			fprintf(stderr, "[is_only_whitespace] Non-whitespace char found: '%c'\n", line[i]);
			return (0);
		}
		i++;
	}
	fprintf(stderr, "[is_only_whitespace] Line is only whitespace\n");
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
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '1')
			has_wall = 1;
		else if (line[i] != ' ')
		{
			fprintf(stderr, "[is_map_start_line] Non-wall/non-space char found: '%c'\n", line[i]);
			return 0;
		}
		i++;
	}
	if (has_wall)
	{
		*in_map = 1;
		fprintf(stderr, "[is_map_start_line] Map start detected at line: %s\n", line);
		return 1;
	}
	return 0;
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
	fprintf(stderr, "[parse_config_settings] Line: %s, settings_type=%d\n", line, settings_type);
	fprintf(stderr, "[DEBUG] Processing config line: %s\n", line);
	if (settings_type >= 1 && settings_type <= 4)
	{
		int ret = get_texture_path(line, game, settings_type);
		fprintf(stderr, "[parse_config_settings] get_texture_path returned %d\n", ret);
		result = ret;
	}
	else if (settings_type == 5 || settings_type == 6)
	{
		int ret = handle_color_settings(line, game, settings_type);
		fprintf(stderr, "[parse_config_settings] handle_color_settings returned %d\n", ret);
		result = ret;
	}
	return (result);
}

/*
Get texture path with duplicate checking
*/
int	get_texture_path(char *line, t_game *game, int settings_type)
{
	char	*path;

	fprintf(stderr, "[get_texture_path] Enter: line='%s', settings_type=%d\n", line, settings_type);
	if (settings_type == 1)
		path = extract_texture_path(line, "NO");
	else if (settings_type == 2)
		path = extract_texture_path(line, "SO");
	else if (settings_type == 3)
		path = extract_texture_path(line, "WE");
	else if (settings_type == 4)
		path = extract_texture_path(line, "EA");

	fprintf(stderr, "[get_texture_path] Extracted path: %s\n", path);

	if (!path || !check_valid_texture_path(path))
	{
		fprintf(stderr, "[get_texture_path] Invalid texture path or path validation failed\n");
		if (path)
			free(path);
		return (-1);
	}
	if (check_duplicate_texture(path, game, settings_type) == -1)
	{
		fprintf(stderr, "[get_texture_path] Duplicate texture detected\n");
		free(path);
		return (-1);
	}
	set_texture_path(path, game, settings_type);
	fprintf(stderr, "[get_texture_path] Texture path set successfully\n");
	return (0);
}

/*
Check for duplicate texture paths
*/
int	check_duplicate_texture(char *path, t_game *game, int settings_type)
{
	fprintf(stderr, "[check_duplicate_texture] Checking path: %s for settings_type: %d\n", path, settings_type);
	if ((settings_type == 1 && game->map.north_texture_path) ||
		(settings_type == 2 && game->map.south_texture_path) ||
		(settings_type == 3 && game->map.west_texture_path) ||
		(settings_type == 4 && game->map.east_texture_path))
	{
		fprintf(stderr, "[check_duplicate_texture] Duplicate detected for settings_type: %d\n", settings_type);
		return (-1);
	}
	fprintf(stderr, "[check_duplicate_texture] No duplicate detected\n");
	return (0);
}

/*
Set the texture path in the game struct
*/
void	set_texture_path(char *path, t_game *game, int settings_type)
{
	fprintf(stderr, "[set_texture_path] Assigning path: %s to settings_type: %d\n", path, settings_type);
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
	fprintf(stderr, "[DEBUG] handle_color_settings: Entering with line='%s', settings_type=%d\n", line, settings_type);
	if (settings_type == 5)
	{
		fprintf(stderr, "[DEBUG] handle_color_settings: Current floor_color={%d,%d,%d}\n",
			game->map.floor_color[0], game->map.floor_color[1], game->map.floor_color[2]);
		if (game->map.floor_color[0] != -1)
		{
			fprintf(stderr, "Error: Duplicate F settings\n");
			return (-1);
		}
		return parse_floor_color(line, game);
	}
	else if (settings_type == 6)
	{
		fprintf(stderr, "[DEBUG] handle_color_settings: Current sky_color={%d,%d,%d}\n",
			game->map.sky_color[0], game->map.sky_color[1], game->map.sky_color[2]);
		if (game->map.sky_color[0] != -1)
		{
			fprintf(stderr, "Error: Duplicate C settings\n");
			return (-1);
		}
		return parse_ceiling_color(line, game);
	}
	return (0);
}

/*
Validate all required configuration settings are present
*/
int	validate_required_config(t_game *game)
{
	fprintf(stderr, "[validate_required_config] Validating required configuration\n");
	if (!game->map.north_texture_path)
	{
		fprintf(stderr, "[validate_required_config] Missing NO (north texture) settings\n");
		return (-1);
	}
	if (!game->map.south_texture_path)
	{
		fprintf(stderr, "[validate_required_config] Missing SO (south texture) settings\n");
		return (-1);
	}
	if (!game->map.west_texture_path)
	{
		fprintf(stderr, "[validate_required_config] Missing WE (west texture) settings\n");
		return (-1);
	}
	if (!game->map.east_texture_path)
	{
		fprintf(stderr, "[validate_required_config] Missing EA (east texture) settings\n");
		return (-1);
	}
	if (game->map.floor_color[0] == -1)
	{
		fprintf(stderr, "[validate_required_config] Missing F (floor color) settings\n");
		return (-1);
	}
	if (game->map.sky_color[0] == -1)
	{
		fprintf(stderr, "[validate_required_config] Missing C (ceiling color) settings\n");
		return (-1);
	}
	fprintf(stderr, "[validate_required_config] All required settings are valid\n");
	return (0);
}

/*
Cleanup and return helper
*/
int	cleanup_and_return(int fd, char *line, int ret_val)
{
	if (line)
		free(line);
	if (fd >= 0)
		close(fd);
	return (ret_val);
}
