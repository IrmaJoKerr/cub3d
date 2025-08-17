/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:29:37 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 10:20:46 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*get_map_path(const char *map_file);
void	init_game(t_game *game, const char *map_file);

/*
Build the full path to the map file.
If the map_file contains a '/', use it as-is.
Otherwise, prepend "maps/" to look in the maps subfolder.
*/
char	*get_map_path(const char *map_file)
{
	char	*full_path;

	full_path = NULL;
	if (ft_strncmp(map_file, "maps/", 5) == 0)
		full_path = ft_strdup(map_file);
	else
		full_path = ft_strjoin("maps/", map_file);
	if (!full_path)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Failed to allocate memory for map path.\n");
		return (NULL);
	}
	if (!check_valid_file_path(full_path))
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

int	check_valid_file_path(const char *path)
{
	int		fd;

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
	int width, height;

	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
	if (!tex->img_ptr)
	{
		ft_fprintf(2, "Texture load failed: %s\n", path);
		exit(1);
	}
	if (width != TEX_WIDTH || height != TEX_HEIGHT)
	{
		ft_fprintf(2, "Invalid texture size (%dx%d): %s\n", width, height, path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len, &tex->endian);
	tex->transparent_color = 0xFF000000;
}



int	count_door_textures(void)
{
	int		count;
	char	path[256];

	count = 0;
	while (count < MAX_DOOR_FRAMES)
	{
		sprintf(path, "textures/doors/door_%d.xpm", count);
		if (!check_valid_file_path(path))
			break ;
		count++;
	}
	return (count);
}

void	load_all_door_textures(t_game *game)
{
	int		i;
	char	path[256];
	int		door_count;

	door_count = count_door_textures();
	if (door_count == 0)
	{
		ft_fprintf(2, "Error: No door textures found in textures/doors/\n");
		exit(1);
	}
	ft_fprintf(1, "Loading %d door textures...\n", door_count);

	i = 0;
	while (i < door_count)
	{
		snprintf(path, sizeof(path), "textures/doors/door_%d.xpm", i);
		game->textures.door_frames[i] = malloc(sizeof(t_image));
		if (!game->textures.door_frames[i])
		{
			ft_fprintf(2, "Error: Failed to allocate door frame %d\n", i);
			exit(1);
		}
		load_texture(game, game->textures.door_frames[i], path);
		usleep(2000); // Small delay between door texture loads
		i++;
	}
	game->textures.door_frame_count = door_count;
	ft_fprintf(1, "✅ Loaded %d door animation frames\n", door_count);
}

void	cleanup_framebuffer(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	game->img.img_ptr = NULL;
	game->img.addr = NULL;
}

int	main(int argc, char **argv)
{
	t_game	*game;
	char	*map_path;

	chk_args(argc, argv);
	map_path = get_map_path(argv[1]);
	if (!map_path)
		return (1);
	alloc_and_init_all(&game);
	init_game(game, map_path);
	free(map_path);
	setup_event_hooks(game);
	mlx_loop_hook(game->mlx_ptr, render_img, game);
	mlx_loop(game->mlx_ptr);
	cleanup(game);
	return (0);
}

/*
Initialises the game window. Mark for refactoring.
Fixed critical logic error: parse_map returns -1 on failure, 1 on success.
*/
void	init_game(t_game *game, const char *map_file)
{
	if (parse_map(map_file, game) < 0)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Failed to parse and validate the map.\n");
		cleanup_early(game);
		exit(EXIT_FAILURE);
	}
	
	/*
	** ================================================================
	** TEMPORARY EXIT - REMOVE WHEN IMPLEMENTING RAYCASTER ENGINE
	** ================================================================
	** 
	** This exit is placed here to allow clean termination after 
	** successful map validation, without entering the MLX game loop.
	** 
	** Once the raycaster engine is implemented, remove this entire
	** TEMPORARY EXIT REMOVED - PROGRAM NOW CONTINUES TO RAYCASTER
	** ================================================================
	*/
	ft_fprintf(1, "\n🎉 MAP VALIDATION COMPLETE - INITIALIZING GRAPHICS ENGINE 🎉\n");
	ft_fprintf(1, "All systems validated. Starting MLX initialization...\n");
	
	/*
	** ================================================================
	** MLX INITIALIZATION CODE - NOW EXECUTING NORMALLY
	** ================================================================
	*/
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
	load_texture(game, game->textures.north_wall, game->map.north_texture_path);
	load_texture(game, game->textures.south_wall, game->map.south_texture_path);
	load_texture(game, game->textures.east_wall, game->map.east_texture_path);
	load_texture(game, game->textures.west_wall, game->map.west_texture_path);
	
	// Load space texture (always loaded like walls)
	load_texture(game, game->textures.space, "textures/space/space.xpm");
	usleep(5000); // Allow space texture to fully initialize
	
	// Load door textures by default
	load_all_door_textures(game);
	
	// Initialize doors from map
	init_doors_from_map(game);
	
	// Initialize minimap system
	setup_minimap(game);
	
	printf("Player position: (%.2f, %.2f)\n", game->curr_x, game->curr_y);
	set_player_to_tile_center(game, game->curr_x, game->curr_y);
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, MAX_WIDTH, MAX_HEIGHT);
	if (!game->img.img_ptr)
	{
		fprintf(stderr, "Error: mlx_new_image failed\n");
		exit(EXIT_FAILURE);
	}
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
									   &game->img.line_len, &game->img.endian);
}
