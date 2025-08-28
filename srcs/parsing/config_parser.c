/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 06:00:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 07:32:02 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int	is_only_whitespace(const char *line);
int	parse_config_settings(char *line, t_game *game);
int	handle_color_settings(char *line, t_game *game, int settings_type);
int	validate_required_config(t_game *game);

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
			return (0);
		}
		i++;
	}
	return (1);
}

/*
Parse individual configuration settings with duplicate checking
*/
int	parse_config_settings(char *line, t_game *game)
{
	int	settings_type;
	int	result;

	settings_type = 0;
	result = 0;
	settings_type = identify_settings_type(line);
	if (settings_type >= 1 && settings_type <= 4)
		result = get_texture_path(line, game, settings_type);
	else if (settings_type == 5 || settings_type == 6)
		result = handle_color_settings(line, game, settings_type);
	return (result);
}

/*
Handle color settings with duplicate checking
*/
int	handle_color_settings(char *line, t_game *game, int settings_type)
{
	if (settings_type == 5)
	{
		if (game->map.floor_color[0] != -1)
		{
			ft_fprintf(2, "Duplicate floor color detected\n");
			return (-1);
		}
		return (parse_floor_color(line, game));
	}
	else if (settings_type == 6)
	{
		if (game->map.sky_color[0] != -1)
		{
			ft_fprintf(2, "Duplicate sky color detected\n");
			return (-1);
		}
		return (parse_ceiling_color(line, game));
	}
	return (0);
}

/*
Validate all required configuration settings are present
*/
int	validate_required_config(t_game *game)
{
	if (!game->map.north_texture_path)
		return (-1);
	if (!game->map.south_texture_path)
		return (-1);
	if (!game->map.west_texture_path)
		return (-1);
	if (!game->map.east_texture_path)
		return (-1);
	if (game->map.floor_color[0] == -1)
		return (-1);
	if (game->map.sky_color[0] == -1)
		return (-1);
	return (0);
}
