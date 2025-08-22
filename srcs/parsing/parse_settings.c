/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:45:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 12:31:43 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		identify_settings_type(const char *line);
char	*extract_texture_path(const char *line, const char *identifier);
int		parse_color_settings(char *line, t_game *game, char settings);

/*
Helper functions for config parser
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

/*
OLD VERSION - BACKUP (monolithic color parsing function)
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
*/

/*
NEW VERSION - Delegates to specific subfunctions for better modularity
*/
int	parse_color_settings(char *line, t_game *game, char settings)
{
	if (settings == 'F')
		return (parse_floor_color(line, game));
	else if (settings == 'C')
		return (parse_ceiling_color(line, game));
	else
		return (-1);
}
