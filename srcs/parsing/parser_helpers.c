/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:45:00 by bleow             #+#    #+#             */
/*   Updated: 2025/07/27 16:32:12 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
 * Helper functions for config parser
 */

int	identify_settings_type(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line + i, "SO ", 3) == 0)
		return (2);
	if (ft_strncmp(line + i, "WE ", 3) == 0)
		return (3);
	if (ft_strncmp(line + i, "EA ", 3) == 0)
		return (4);
	if (ft_strncmp(line + i, "F ", 2) == 0)
		return (5);
	if (ft_strncmp(line + i, "C ", 2) == 0)
		return (6);
	if (ft_strncmp(line + i, "R ", 2) == 0)
		return (7);
	return (0);
}

char	*extract_texture_path(const char *line, const char *identifier)
{
	int		i;
	int		start;
	int		len;
	char	*path;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	i += ft_strlen(identifier);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	len = i - start;
	if (len == 0)
		return (NULL);
	path = malloc(sizeof(char) * (len + 1));
	if (!path)
		return (NULL);
	ft_strncpy(path, line + start, len);
	path[len] = '\0';
	return (path);
}

int	parse_color_settings(char *line, t_game *game, char settings)
{
	char	*values;
	int		color[3];
	int		result;

	if (settings == 'F')
	{
		values = extract_color_values(line, "F");
		result = validate_color_values(values, color);
		if (result == 0)
		{
			game->map.floor_color[0] = color[0];
			game->map.floor_color[1] = color[1];
			game->map.floor_color[2] = color[2];
		}
	}
	else if (settings == 'C')
	{
		values = extract_color_values(line, "C");
		result = validate_color_values(values, color);
		if (result == 0)
		{
			game->map.sky_color[0] = color[0];
			game->map.sky_color[1] = color[1];
			game->map.sky_color[2] = color[2];
		}
	}
	else
		result = -1;
	if (values)
		free(values);
	return (result);
}

char	*extract_color_values(const char *line, const char *identifier)
{
	int		i;
	int		start;
	char	*values;

	i = ft_strlen(identifier);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	values = malloc(sizeof(char) * (i - start + 1));
	if (!values)
		return (NULL);
	ft_strncpy(values, line + start, i - start);
	values[i - start] = '\0';
	return (values);
}

int	validate_color_values(const char *values, int color[3])
{
	int		i;
	int		num_count;
	char	**numbers;

	if (!values)
		return (-1);
	numbers = ft_split(values, ',');
	if (!numbers)
		return (-1);
	num_count = 0;
	while (numbers[num_count])
		num_count++;
	if (num_count != 3)
	{
		ft_free_2d(numbers, num_count);
		return (-1);
	}
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(numbers[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			ft_free_2d(numbers, num_count);
			return (-1);
		}
		i++;
	}
	ft_free_2d(numbers, num_count);
	return (0);
}

int	parse_resolution_settings(char *line, t_game *game)
{
	char	*values;
	int		resolution[2];
	int		result;

	values = extract_resolution_values(line, "R");
	result = validate_resolution_values(values, resolution);
	if (result == 0)
	{
		game->map.resolution[0] = resolution[0];
		game->map.resolution[1] = resolution[1];
	}
	if (values)
		free(values);
	return (result);
}

char	*extract_resolution_values(const char *line, const char *identifier)
{
	int		i;
	int		start;
	char	*values;

	i = ft_strlen(identifier);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	values = malloc(sizeof(char) * (i - start + 1));
	if (!values)
		return (NULL);
	ft_strncpy(values, line + start, i - start);
	values[i - start] = '\0';
	return (values);
}

int	validate_resolution_values(const char *values, int resolution[2])
{
	int		i;
	int		num_count;
	char	**numbers;

	if (!values)
		return (-1);
	numbers = ft_split(values, ' ');
	if (!numbers)
		return (-1);
	num_count = 0;
	while (numbers[num_count])
		num_count++;
	if (num_count != 2)
	{
		ft_free_2d(numbers, num_count);
		return (-1);
	}
	i = 0;
	while (i < 2)
	{
		resolution[i] = ft_atoi(numbers[i]);
		if (resolution[i] <= 0)
		{
			ft_free_2d(numbers, num_count);
			return (-1);
		}
		i++;
	}
	ft_free_2d(numbers, num_count);
	return (0);
}
