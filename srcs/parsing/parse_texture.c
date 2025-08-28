/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:23:13 by bleow             #+#    #+#             */
/*   Updated: 2025/08/25 19:27:57 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		get_texture_path(char *line, t_game *game, int settings_type);
int		check_duplicate_texture(t_game *game, int settings_type);
void	set_texture_path(char *path, t_game *game, int settings_type);
int		check_valid_texture_path(const char *path);

/*
Get texture path with duplicate checking
*/
int	get_texture_path(char *line, t_game *game, int settings_type)
{
	char	*path;

	path = NULL;
	if (settings_type == 1)
		path = extract_texture_path(line, "NO");
	else if (settings_type == 2)
		path = extract_texture_path(line, "SO");
	else if (settings_type == 3)
		path = extract_texture_path(line, "WE");
	else if (settings_type == 4)
		path = extract_texture_path(line, "EA");
	if (!path || (check_valid_texture_path(path) == -1))
	{
		if (path)
			ft_safefree((void **)&path);
		return (-1);
	}
	if (check_duplicate_texture(game, settings_type) == -1)
	{
		ft_safefree((void **)&path);
		return (-1);
	}
	if (path)
		set_texture_path(path, game, settings_type);
	return (0);
}

/*
Check for duplicate texture paths
*/
int	check_duplicate_texture(t_game *game, int settings_type)
{
	if ((settings_type == 1 && game->map.north_texture_path)
		|| (settings_type == 2 && game->map.south_texture_path)
		|| (settings_type == 3 && game->map.west_texture_path)
		|| (settings_type == 4 && game->map.east_texture_path))
	{
		ft_fprintf(2, "Duplicate texture detected for settings type: %d\n",
			settings_type);
		return (-1);
	}
	return (0);
}

/*
Set the texture path in the game struct
*/
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
Texture path validation with XMP extension check
*/
int	check_valid_texture_path(const char *path)
{
	int		fd;

	if (!path || ft_strlen(path) == 0)
	{
		ft_fprintf(2, "Error: Empty texture path\n");
		return (-1);
	}
	if (!validate_xmp_extension(path))
	{
		ft_fprintf(2, "Error: Texture file must have .xpm extension: %s\n",
			path);
		return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error: Cannot access texture file: %s\n", path);
		return (-1);
	}
	close(fd);
	return (0);
}
