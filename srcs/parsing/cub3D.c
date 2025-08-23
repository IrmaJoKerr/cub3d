/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:29:37 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 05:13:49 by bleow            ###   ########.fr       */
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
	while (i <= 7)
	{
		ft_strcpy(path, DOORS_TEXTURE);
		ft_strcat(path, "door_");
		num = ft_itoa(i);
		ft_strcat(path, num);
		free(num);
		ft_strcat(path, ".xpm");
		if (!check_valid_file_path(path))
			return (0);
		if (!load_door_texture(game, path, i))
			return (0);
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
	ft_fprintf(2, "Error: Map file not found: %s\n", input);
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
Load a texture from file and store it in the t_image struct
*/
int	load_texture(t_game *game, t_image *tex, char *path)
{
	int	width;
	int	height;

	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
	if (!tex->img_ptr)
	{
		ft_fprintf(2, "Texture load failed: %s\n", path);
		return (-1);
	}
	if (width != TEX_WIDTH || height != TEX_HEIGHT)
	{
		ft_fprintf(2, "Invalid texture size (%dx%d): %s\n", width, height,
			path);
		return (-1);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	tex->transparent_color = 0xFF000000;
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
	if (populate_map_array(map_path, game) < 0)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Failed to populate map array.\n");
		cleanup_later(game, map_path);
		exit(EXIT_FAILURE);
	}
	ft_fprintf(1, "\nMAP VALIDATION COMPLETE\n");
	ft_fprintf(1, "Starting MLX initialization\n");
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Failed to initialize MiniLibX.\n");
		cleanup_early(game, map_path);
		exit(EXIT_FAILURE);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1920, 1080, "cub3D");
	if (!game->win_ptr)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Failed to create a new window.\n");
		cleanup_later(game, map_path);
		exit(EXIT_FAILURE);
	}
}

/*
Initialises the game state and loads all required textures
*/
void	init_game(t_game *game, const char *map_file)
{
	if (parse_map_1(map_file, game) < 0 && parse_map_2(map_file, game) < 0)
	{
		ft_fprintf(2, "Error: Failed to parse map file.\n");
		cleanup_early(game, map_file);
		exit(EXIT_FAILURE);
	}
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
	if (!check_builtin_textures(game))
	{
		ft_fprintf(2, "Error: Missing builtin textures.\n");
		return (-1);
	}
	if (load_texture(game, game->textures.north_wall,
			game->map.north_texture_path) < 0 || (load_texture(game,
				game->textures.south_wall, game->map.south_texture_path) < 0)
		|| (load_texture(game, game->textures.east_wall,
				game->map.east_texture_path) < 0) || (load_texture(game,
				game->textures.west_wall, game->map.west_texture_path) < 0)
		|| (load_texture(game, game->textures.space, SPACE_TEXTURE) < 0))
	{
		ft_fprintf(2, "Error: Failed to load one or more textures.\n");
		return (-1);
	}
	init_doors_from_map(game);
	return (0);
}
