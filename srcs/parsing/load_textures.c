/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 04:00:09 by bleow             #+#    #+#             */
/*   Updated: 2025/08/29 17:28:31 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int	load_mlx_textures(t_game *game);
int	load_texture(t_game *game, t_image *tex, char *path);
int	load_wall_textures(t_game *game);
int	load_door_texture(t_game *game, char *path, int i);

/*
Load all main (non-minimap) required textures for the game
*/
int	load_mlx_textures(t_game *game)
{
	if (check_builtin_textures(game) == -1)
	{
		ft_fprintf(2, "Error: Check_builtin_textures failed\n");
		return (-1);
	}
	if (load_wall_textures(game) < 0)
	{
		ft_fprintf(2, "Error: Load_wall_textures failed\n");
		return (-1);
	}
	if (load_texture(game, game->textures.space, SPACE_TEXTURE) < 0)
	{
		ft_fprintf(2, "Error: Load_texture for space failed\n");
		return (-1);
	}
	usleep(1000);
	return (0);
}

/*
Load a texture from file and store it in the t_image struct
*/
int	load_texture(t_game *game, t_image *tex, char *path)
{
	int	width;
	int	height;

	if (!game)
		return (-1);
	if (!tex)
	{
		ft_fprintf(2, "Error: Texture pointer is NULL\n");
		return (-1);
	}
	if (!path || ft_strlen(path) == 0)
		return (-1);
	if (!game->mlx_ptr)
		return (-1);
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
	if (!tex->img_ptr)
		return (-1);
	if (width != TEX_WIDTH || height != TEX_HEIGHT)
		return (-1);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (-1);
	tex->transparent_color = 0xFF000000;
	return (0);
}

/*
Load all wall textures for the game.
*/
int	load_wall_textures(t_game *game)
{
	if (load_texture(game, game->textures.north_wall,
			game->map.north_texture_path) < 0)
	{
		ft_fprintf(2, "Error: Load_texture for north_wall failed\n");
		return (-1);
	}
	if (load_texture(game, game->textures.south_wall,
			game->map.south_texture_path) < 0)
	{
		ft_fprintf(2, "Error: Load_texture for south_wall failed\n");
		return (-1);
	}
	if (load_texture(game, game->textures.east_wall,
			game->map.east_texture_path) < 0)
	{
		ft_fprintf(2, "Error: Load_texture for east_wall failed\n");
		return (-1);
	}
	if (load_texture(game, game->textures.west_wall,
			game->map.west_texture_path) < 0)
	{
		ft_fprintf(2, "Error: Load_texture for west_wall failed\n");
		return (-1);
	}
	return (0);
}

/*
Load a door texture and store it in the game struct
*/
int	load_door_texture(t_game *game, char *path, int i)
{
	if (i >= MAX_DOOR_FRAMES)
		return (0);
	game->textures.door_frames[i] = malloc(sizeof(t_image));
	if (!game->textures.door_frames[i])
		return (0);
	if (!path)
	{
		free(game->textures.door_frames[i]);
		game->textures.door_frames[i] = NULL;
		return (0);
	}
	if (!game->mlx_ptr)
	{
		free(game->textures.door_frames[i]);
		game->textures.door_frames[i] = NULL;
		return (0);
	}
	if (load_texture(game, game->textures.door_frames[i], path) < 0)
	{
		free(game->textures.door_frames[i]);
		game->textures.door_frames[i] = NULL;
		return (0);
	}
	game->textures.door_frame_count = i + 1;
	return (1);
}
