/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserutil_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 05:15:13 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 09:43:17 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Parse configuration settingss from .cub file
 * Returns 0 on success, -1 on error
 */
int	parse_configuration(const char *file, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line && ft_strlen(line) > 0)
		{
			if (parse_settings(line, game) == -1)
			{
				free(line);
				close(fd);
				return (-1);
			}
		}
		free(line);
	}
	close(fd);
	return (0);
}

/**
 * Parse individual settings line (texture, color, or resolution)
 * Returns 0 on success, -1 on error, 1 if not a settings
 */
int	parse_settings(char *line, t_game *game)
{
	char	*path;
	int		settings_type;

	settings_type = identify_settings_type(line);
	if (settings_type == 0)
		return (1);
	if (settings_type == 1)
	{
		path = extract_texture_path(line, "NO");
		if (!path || !check_valid_file_path(path))
			return (-1);
		game->map.north_texture_path = path;
	}
	else if (settings_type == 2)
	{
		path = extract_texture_path(line, "SO");
		if (!path || !check_valid_file_path(path))
			return (-1);
		game->map.south_texture_path = path;
	}
	else if (settings_type == 3)
	{
		path = extract_texture_path(line, "WE");
		if (!path || !check_valid_file_path(path))
			return (-1);
		game->map.west_texture_path = path;
	}
	else if (settings_type == 4)
	{
		path = extract_texture_path(line, "EA");
		if (!path || !check_valid_file_path(path))
			return (-1);
		game->map.east_texture_path = path;
	}
	else if (settings_type == 5)
	{
		if (parse_color_settings(line, game, 'F') != 0)
			return (-1);
	}
	else if (settings_type == 6)
	{
		if (parse_color_settings(line, game, 'C') != 0)
			return (-1);
	}
	else if (settings_type == 7)
	{
		if (parse_resolution_settings(line, game) != 0)
			return (-1);
	}
	return (0);
}

/**
 * Extract texture path from settings line using ft_substr
 * Returns allocated string or NULL on error
 */
char	*extract_texture_path(const char *line, const char *identifier)
{
	int		i;
	int		start;
	int		end;
	int		id_len;

	if (!line || !identifier)
		return (NULL);
	id_len = ft_strlen(identifier);
	i = 0;
	i = skip_whitespace(line, i);
	if (ft_strncmp(line + i, identifier, id_len) != 0)
		return (NULL);
	i += id_len;
	i = skip_whitespace(line, i);
	start = i;
	while (line[i] && !ft_isspace(line[i]) && ft_isascii(line[i]))
		i++;
	end = i;
	if (start >= end)
		return (NULL);
	return (ft_substr(line, start, end - start));
}

/**
 * Validate texture path
 * Returns 1 if valid, 0 if invalid
 */
/**
 * Skip whitespace characters starting from position start
 * Returns new position after whitespace
 */
int	skip_whitespace(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

/**
 * Identify settings type from line
 * Returns: 0=not a settings, 1=NO, 2=SO, 3=WE, 4=EA, 5=F, 6=C, 7=R
 */
int	identify_settings_type(const char *line)
{
	int	i;

	if (!line)
		return (0);
	i = skip_whitespace(line, 0);
	if (ft_strncmp(line + i, "NO", 2) == 0 && ft_isspace(line[i + 2]))
		return (1);
	else if (ft_strncmp(line + i, "SO", 2) == 0 && ft_isspace(line[i + 2]))
		return (2);
	else if (ft_strncmp(line + i, "WE", 2) == 0 && ft_isspace(line[i + 2]))
		return (3);
	else if (ft_strncmp(line + i, "EA", 2) == 0 && ft_isspace(line[i + 2]))
		return (4);
	else if (line[i] == 'F' && ft_isspace(line[i + 1]))
		return (5);
	else if (line[i] == 'C' && ft_isspace(line[i + 1]))
		return (6);
	else if (line[i] == 'R' && ft_isspace(line[i + 1]))
		return (7);
	return (0);
}

/**
 * Extract color/resolution values from settings line
 * Returns allocated string containing the values or NULL on error
 */
char	*extract_color_values(const char *line, const char *identifier)
{
	int		i;
	int		start;
	int		end;
	int		id_len;

	if (!line || !identifier)
		return (NULL);
	id_len = ft_strlen(identifier);
	i = skip_whitespace(line, 0);
	if (ft_strncmp(line + i, identifier, id_len) != 0)
		return (NULL);
	i += id_len;
	i = skip_whitespace(line, i);
	start = i;
	end = ft_strlen(line);
	while (end > start && ft_isspace(line[end - 1]))
		end--;
	if (start >= end)
		return (NULL);
	return (ft_substr(line, start, end - start));
}

/**
 * Extract resolution values from R settings line
 */
char	*extract_resolution_values(const char *line, const char *identifier)
{
	return (extract_color_values(line, identifier));
}

/**
 * Parse color settings (F or C)
 * Returns 0 on success, -1 on error
 */
int	parse_color_settings(char *line, t_game *game, char settings)
{
	char	*values;
	char	identifier[2];
	int		*color_array;

	identifier[0] = settings;
	identifier[1] = '\0';
	values = extract_color_values(line, identifier);
	if (!values)
		return (-1);
	if (settings == 'F')
		color_array = game->map.floor_color;
	else if (settings == 'C')
		color_array = game->map.sky_color;
	else
	{
		free(values);
		return (-1);
	}
	if (validate_color_values(values, color_array) != 0)
	{
		free(values);
		return (-1);
	}
	free(values);
	return (0);
}

/**
 * Parse resolution settings (R)
 * Returns 0 on success, -1 on error
 */
int	parse_resolution_settings(char *line, t_game *game)
{
	char	*values;

	values = extract_resolution_values(line, "R");
	if (!values)
		return (-1);
	if (validate_resolution_values(values, game->map.resolution) != 0)
	{
		free(values);
		return (-1);
	}
	free(values);
	return (0);
}

/**
 * Validate color values string and convert to integers
 * Format: "R,G,B" where each value is 0-255
 * Returns 0 on success, -1 on error
 */
int	validate_color_values(const char *values, int color[3])
{
	char	**rgb_parts;
	int		i;
	int		value;

	if (!values)
		return (-1);
	rgb_parts = ft_split(values, ',');
	if (!rgb_parts)
		return (-1);
	if (ft_arrlen(rgb_parts) != 3)
	{
		ft_free_2d(rgb_parts, ft_arrlen(rgb_parts));
		return (-1);
	}
	i = 0;
	while (i < 3)
	{
		if (!is_valid_number_string(rgb_parts[i]))
		{
			ft_free_2d(rgb_parts, 3);
			return (-1);
		}
		value = ft_atoi(rgb_parts[i]);
		if (value < MIN_RGB || value > MAX_RGB)
		{
			ft_free_2d(rgb_parts, 3);
			return (-1);
		}
		color[i] = value;
		i++;
	}
	ft_free_2d(rgb_parts, 3);
	return (0);
}

/**
 * Validate resolution values string and convert to integers
 * Format: "WIDTH HEIGHT" where WIDTH <= 1920, HEIGHT <= 1080
 * Returns 0 on success, -1 on error
 */
int	validate_resolution_values(const char *values, int resolution[2])
{
	char	**res_parts;
	int		width;
	int		height;

	if (!values)
		return (-1);
	res_parts = ft_split(values, ' ');
	if (!res_parts)
		return (-1);
	if (ft_arrlen(res_parts) != 2)
	{
		ft_free_2d(res_parts, ft_arrlen(res_parts));
		return (-1);
	}
	if (!is_valid_number_string(res_parts[0])
		|| !is_valid_number_string(res_parts[1]))
	{
		ft_free_2d(res_parts, 2);
		return (-1);
	}
	width = ft_atoi(res_parts[0]);
	height = ft_atoi(res_parts[1]);
	if (width <= 0 || width > MAX_WIDTH || height <= 0 || height > MAX_HEIGHT)
	{
		ft_free_2d(res_parts, 2);
		return (-1);
	}
	resolution[0] = width;
	resolution[1] = height;
	ft_free_2d(res_parts, 2);
	return (0);
}

/**
 * Check if string contains only digits and whitespace
 * Returns 1 if valid, 0 if invalid
 */
int	is_valid_number_string(const char *str)
{
	int	i;
	int	has_digit;

	if (!str)
		return (0);
	i = 0;
	has_digit = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		has_digit = 1;
		i++;
	}
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (has_digit && str[i] == '\0');
}
