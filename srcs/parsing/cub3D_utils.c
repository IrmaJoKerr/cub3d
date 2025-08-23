/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 06:27:27 by bleow             #+#    #+#             */
/*   Updated: 2025/08/23 08:00:36 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
char	*get_map_path(char *input);
int		check_valid_file_path(char *path);
void	load_texture(t_game *game, t_image *tex, char *path);

/*
Unified map path resolution supporting valid/invalid subfolders.
If input starts with maps/valid/ or maps/invalid/, use as-is if exists.
Otherwise, try maps/invalid/ then maps/valid/. Returns first found or error.
*/
char	*get_map_path(char *input)
{
	char	*test_path;

	if (ft_strncmp(input, "maps/valid/", 11) == 0
		|| ft_strncmp(input, "maps/invalid/", 13) == 0)
	{
		if (check_valid_file_path(input))
			return (ft_strdup(input));
	}
	else
	{
		test_path = ft_strjoin("maps/invalid/", input);
		if (check_valid_file_path(test_path))
			return (test_path);
		free(test_path);
		test_path = ft_strjoin("maps/valid/", input);
		if (check_valid_file_path(test_path))
			return (test_path);
		free(test_path);
	}
	ft_fprintf(2, "Error: Map file not found: %s\n", input);
	return (NULL);
}

int	check_valid_file_path(char *path)
{
	int	fd;

	if (!path || ft_strlen(path) == 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

void	load_texture(t_game *game, t_image *tex, char *path)
{
	int	width;
	int	height;

	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
	if (!tex->img_ptr)
	{
		ft_fprintf(2, "Texture load failed: %s\n", path);
		exit(1);
	}
	if (width != TEX_WIDTH || height != TEX_HEIGHT)
	{
		ft_fprintf(2, "Invalid texture size (%dx%d): %s\n", width, height,
			path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	tex->transparent_color = 0xFF000000;
}

// int	count_door_textures(void)
// {
// 	int	count;
// 	char	path[256];

// 	count = 0;
// 	while (count < MAX_DOOR_FRAMES)
// 	{
// 		sprintf(path, "textures/doors/door_%d.xpm", count);
// 		if (!check_valid_file_path(path))
// 			break ;
// 		count++;
// 	}
// 	return (count);
// }

int		load_door_texture(t_game *game, char *path, int i)
{
   if (i >= MAX_DOOR_FRAMES)
   {
	   ft_fprintf(2, "Error: Too many door textures loaded\n");
	   return (0);
   }
   game->textures.door_frames[i] = malloc(sizeof(t_image));
   if (!game->textures.door_frames[i])
   {
	   ft_fprintf(2, "Error: Failed to allocate door frame %d\n", i);
	   return (0);
   }
   load_texture(game, game->textures.door_frames[i], path);
   game->textures.door_frame_count = i + 1;
   ft_fprintf(2, "Loaded door texture: %s\n", path);
   return (1);
}

/*
Initialises the game window. Mark for refactoring.
Fixed critical logic error: parse_map returns -1 on failure, 1 on success.
*/
void	init_mlx_sys(t_game *game)
{
	ft_fprintf(1, "\nMAP VALIDATION COMPLETE\n");
	ft_fprintf(1, "Starting MLX initialization\n");
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Failed to initialize MiniLibX.\n");
		cleanup_early(game);
		exit(EXIT_FAILURE);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1920, 1080, "cub3D");
	if (!game->win_ptr)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Failed to create a new window.\n");
		cleanup_later(game);
		exit(EXIT_FAILURE);
	}
}

/*
 * Robust init_game implementation migrated from cub3d-bing.
 */
void	init_game(t_game *game, const char *map_file)
{
	if (parse_map(map_file, game) < 0)
	{
		cleanup_early(game);
		exit(EXIT_FAILURE);
	}
	init_mlx_sys(game);
	load_texture(game, game->textures.north_wall, game->map.north_texture_path);
	load_texture(game, game->textures.south_wall, game->map.south_texture_path);
	load_texture(game, game->textures.east_wall, game->map.east_texture_path);
	load_texture(game, game->textures.west_wall, game->map.west_texture_path);
	load_texture(game, game->textures.space, "textures/space/space.xpm");
	usleep(5000);
	// DEPRECATION CANDIDATE: load_all_door_textures is replaced by load_door_texture
	// load_all_door_textures(game);
	init_doors_from_map(game);
	setup_minimap(game);
	printf("Player position: (%.2f, %.2f)\n", game->curr_x, game->curr_y);
	set_player_start_position(game, game->curr_x, game->curr_y);
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, MAX_WIDTH, MAX_HEIGHT);
	if (!game->img.img_ptr)
	{
		fprintf(stderr, "Error: mlx_new_image failed\n");
		exit(EXIT_FAILURE);
	}
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
}
