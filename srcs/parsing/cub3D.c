/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:29:37 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 17:46:35 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
char	*get_map_path(char *map_file);
int		check_valid_file_path(char *path);
int	load_texture(t_game *game, t_image *tex, char *path);
int		check_builtin_textures(t_game *game);
void	init_game(t_game *game, const char *map_file);

/*
Check that all required builtin textures exist and load door textures
*/
int	check_builtin_textures(t_game *game)
{
	int		i;
	char	path[256];
	char	*num;

	if (!check_valid_file_path(SPACE_TEXTURE))
		return (0);
	i = 0;
	while (i < 8) // Ensure the loop stops at 8
	{
		ft_strcpy(path, DOORS_TEXTURE);
		ft_strcat(path, "door_");
		num = ft_itoa(i);
		ft_strcat(path, num);
		free(num);
		ft_strcat(path, ".xpm");
		fprintf(stderr, "[DEBUG] Constructed path: %s\n", path);
		if (!check_valid_file_path(path))
		{
			fprintf(stderr, "[ERROR] Invalid path: %s\n", path);
			cleanup_door_frames(game);
			return (0);
		}
		if (!load_door_texture(game, path, i))
		{
			fprintf(stderr, "[ERROR] Failed to load door texture: %s\n", path);
			cleanup_door_frames(game);
			return (0);
		}
		i++;
	}
	return (1);
}

/*
Resolve the correct map path based on input and available files
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
		ft_safefree((void **)&test_path);
		test_path = ft_strjoin("maps/valid/", input);
		if (check_valid_file_path(test_path))
			return (test_path);
		ft_safefree((void **)&test_path);
	}
	fprintf(stderr, "Error: Map file not found: %s\n", input);
	return (NULL);
}

/*
Check if a file path is valid and accessible
*/
int	check_valid_file_path(char *path)
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

/*
Allocate memory for a texture structure
*/
static t_image	*allocate_texture(void)
{
	t_image	*texture;

	texture = ft_calloc(1, sizeof(t_image));
	if (!texture)
	{
		perror("Error: Failed to allocate memory for texture structure\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "[DEBUG] Allocated memory for texture at address: %p\n", (void *)texture);
	return (texture);
}

/*
Load a texture from file and store it in the t_image struct
*/
int	load_texture(t_game *game, t_image *tex, char *path)
{
	int	width;
	int	height;

	fprintf(stderr, "[DEBUG] load_texture: Entering with path='%s'\n", path ? path : "NULL");
	if (!game)
	{
		fprintf(stderr, "[ERROR] Game struct is NULL\n");
		return (-1);
	}
	if (!tex)
	{
		fprintf(stderr, "[DEBUG] Texture struct is NULL. Allocating memory.\n");
		tex = allocate_texture();
	}
	if (!path || ft_strlen(path) == 0)
	{
		fprintf(stderr, "[ERROR] Invalid path: %s\n", path ? path : "NULL");
		return (-1);
	}
	if (!game->mlx_ptr)
	{
		fprintf(stderr, "[ERROR] mlx_ptr is NULL\n");
		return (-1);
	}
	fprintf(stderr, "[DEBUG] mlx_ptr address: %p\n", (void *)game->mlx_ptr);
	fprintf(stderr, "[DEBUG] Texture struct address: %p\n", (void *)tex);
	fprintf(stderr, "[DEBUG] Path: %s\n", path);
	fprintf(stderr, "[DEBUG] Loading texture using mlx_xpm_file_to_image\n");
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
	if (!tex->img_ptr)
	{
		fprintf(stderr, "[ERROR] Texture load failed: %s\n", path);
		return (-1);
	}
	fprintf(stderr, "[DEBUG] Texture loaded successfully. Dimensions: %dx%d\n", width, height);
	if (width != TEX_WIDTH || height != TEX_HEIGHT)
	{
		fprintf(stderr, "[ERROR] Invalid texture size (%dx%d): %s\n", width, height, path);
		return (-1);
	}
	fprintf(stderr, "[DEBUG] Getting texture data address\n");
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		fprintf(stderr, "[ERROR] Failed to retrieve texture data address\n");
		return (-1);
	}
	fprintf(stderr, "[DEBUG] Texture data address retrieved successfully\n");
	tex->transparent_color = 0xFF000000;
	fprintf(stderr, "[DEBUG] Texture loaded and initialized successfully\n");
	return (0);
}

/*
Main entry point for the cub3D program
*/
int	main(int argc, char **argv)
{
	t_game	*game;
	char	*map_path;

	chk_args(argc, argv);
	map_path = get_map_path(argv[1]);
	if (!map_path)
		return (1);
	alloc_and_init_all(&game);
	if (parse_map_1(map_path, game) < 0)
	{
		fprintf(stderr, "Error: Failed to parse map file.\n");
		cleanup_early(game, map_path);
		exit(EXIT_FAILURE);
	}
	if (parse_map_2(map_path, game) < 0)
	{
		fprintf(stderr, "Error: Failed to parse map file.\n");
		cleanup_early(game, map_path);
		exit(EXIT_FAILURE);
	}
	init_game(game, map_path);
	free(map_path);
	setup_event_hooks(game);
	mlx_loop_hook(game->mlx_ptr, render_img, game);
	mlx_loop(game->mlx_ptr);
	cleanup(game);
	return (0);
}

/*
Initialises the game window and MLX system
*/
void	init_mlx_sys(t_game *game, const char *map_path)
{
	fprintf(stdout, "\nMAP VALIDATION COMPLETE\n");
	fprintf(stdout, "Starting MLX initialization\n");
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		fprintf(stderr, "Error: \n");
		fprintf(stderr, "Failed to initialize MiniLibX.\n");
		cleanup_early(game, map_path);
		exit(EXIT_FAILURE);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1920, 1080, "cub3D");
	if (!game->win_ptr)
	{
		fprintf(stderr, "Error: \n");
		fprintf(stderr, "Failed to create a new window.\n");
		cleanup_later(game, map_path);
		exit(EXIT_FAILURE);
	}
	usleep(1000);
	if (populate_map_array(map_path, game) < 0)
	{
		fprintf(stderr, "Error: \n");
		fprintf(stderr, "Failed to populate map array.\n");
		cleanup_later(game, map_path);
		exit(EXIT_FAILURE);
	}
}

/*
Initialises the game state and loads all required textures
*/
void	init_game(t_game *game, const char *map_file)
{
	init_mlx_sys(game, map_file);
	if (load_textures(game) < 0)
	{
		cleanup_later(game, map_file);
		exit(EXIT_FAILURE);
	}
	if (setup_minimap(game) < 0)
	{
		cleanup_later(game, map_file);
		exit(EXIT_FAILURE);
	}
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, MAX_WIDTH, MAX_HEIGHT);
	if (!game->img.img_ptr)
	{
		fprintf(stderr, "Error: mlx_new_image failed\n");
		exit(EXIT_FAILURE);
	}
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
}

int	load_textures(t_game *game)
{
	fprintf(stderr, "[DEBUG] load_textures: Checking builtin textures\n");
	if (!check_builtin_textures(game))
	{
		fprintf(stderr, "Error: Missing builtin textures.\n");
		return (-1);
	}
	fprintf(stderr, "[DEBUG] load_textures: Loading north_wall texture: %s\n", game->map.north_texture_path);
	if (load_texture(game, game->textures.north_wall, game->map.north_texture_path) < 0)
		return (-1);
	fprintf(stderr, "[DEBUG] load_textures: Loading south_wall texture: %s\n", game->map.south_texture_path);
	if (load_texture(game, game->textures.south_wall, game->map.south_texture_path) < 0)
		return (-1);
	fprintf(stderr, "[DEBUG] load_textures: Loading east_wall texture: %s\n", game->map.east_texture_path);
	if (load_texture(game, game->textures.east_wall, game->map.east_texture_path) < 0)
		return (-1);
	fprintf(stderr, "[DEBUG] load_textures: Loading west_wall texture: %s\n", game->map.west_texture_path);
	if (load_texture(game, game->textures.west_wall, game->map.west_texture_path) < 0)
		return (-1);
	fprintf(stderr, "[DEBUG] load_textures: Loading space texture: %s\n", SPACE_TEXTURE);
	if (load_texture(game, game->textures.space, SPACE_TEXTURE) < 0)
		return (-1);
	init_doors_from_map(game);
	return (0);
}
