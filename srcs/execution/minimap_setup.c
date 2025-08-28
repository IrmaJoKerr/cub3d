/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 05:22:01 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 05:24:48 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int	setup_minimap(t_game *game);
int	alloc_minimap_memory(t_game *game, t_mini *minimap);
int	load_minimap_tiles(t_game *game);
int	load_mini_tex(t_game *game, t_image *tex, char *path);

/*
Set up the minimap images and data buffers.
*/
int	setup_minimap(t_game *game)
{
	if (!game || !game->mlx_ptr)
	{
		ft_fprintf(2, "setup_minimap failed: game or mlx_ptr is NULL\n");
		return (-1);
	}
	init_minimap_struct(game, &game->minimap);
	if (load_minimap_tiles(game) == -1)
	{
		ft_fprintf(2, "setup_minimap failed: load_minimap_tiles failed\n");
		return (-1);
	}
	if (alloc_minimap_memory(game, &game->minimap) == -1)
	{
		ft_fprintf(2, "setup_minimap failed: alloc_minimap_memory failed\n");
		return (-1);
	}
	usleep(1000);
	generate_full_minimap(game);
	ft_fprintf(2, "setup_minimap completed successfully\n");
	return (0);
}

/*
Allocate memory for minimap data buffers and create images.
*/
int	alloc_minimap_memory(t_game *game, t_mini *minimap)
{
	minimap->full_map_img = mlx_new_image(game->mlx_ptr, minimap->width,
			minimap->height);
	if (!minimap->full_map_img)
		return (-1);
	minimap->full_map_data = mlx_get_data_addr(minimap->full_map_img,
			&minimap->full_map_bpp, &minimap->full_map_sl,
			&minimap->full_map_endian);
	if (!minimap->full_map_data)
		return (-1);
	minimap->minimap_img = mlx_new_image(game->mlx_ptr, 180, 180);
	if (!minimap->minimap_img)
		return (-1);
	minimap->minimap_data = mlx_get_data_addr(minimap->minimap_img,
			&minimap->minimap_bpp, &minimap->minimap_sl,
			&minimap->minimap_endian);
	if (!minimap->minimap_data)
		return (-1);
	ft_fprintf(2, "Memory allocation for minimap data successful\n");
	return (0);
}

/*
Load minimap tile images for wall, floor, door, and space.
*/
int	load_minimap_tiles(t_game *game)
{
	if (load_mini_tex(game, game->minimap.wall, "textures/minimap/wall.xpm")
		< 0)
	{
		ft_fprintf(2, "Error: Failed to load wall texture for minimap.\n");
		return (-1);
	}
	if (load_mini_tex(game, game->minimap.floor, "textures/minimap/floor.xpm")
		< 0)
	{
		ft_fprintf(2, "Error: Failed to load floor texture for minimap.\n");
		return (-1);
	}
	if (load_mini_tex(game, game->minimap.door, "textures/minimap/door.xpm")
		< 0)
	{
		ft_fprintf(2, "Error: Failed to load door texture for minimap.\n");
		return (-1);
	}
	if (load_mini_tex(game, game->minimap.space, "textures/minimap/space.xpm")
		< 0)
	{
		ft_fprintf(2, "Error: Failed to load space texture for minimap.\n");
		return (-1);
	}
	return (0);
}

/*
Load minimap texture images with specific width and height validation.
*/
int	load_mini_tex(t_game *game, t_image *tex, char *path)
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
	if (width != MIN_TEX_WIDTH || height != MIN_TEX_HEIGHT)
		return (-1);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (-1);
	tex->transparent_color = 0xFF000000;
	return (0);
}
