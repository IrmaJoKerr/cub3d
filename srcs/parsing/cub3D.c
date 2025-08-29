/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:29:37 by bleow             #+#    #+#             */
/*   Updated: 2025/08/29 17:29:17 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		check_builtin_textures(t_game *game);
int		main(int argc, char **argv);
void	init_mlx_sys(t_game *game, const char *map_path);
void	init_game(t_game *game, const char *map_file);

/*
Check that all required builtin textures exist and load door textures
*/
int	check_builtin_textures(t_game *game)
{
	int		i;
	char	*path;

	if (!check_valid_file_path(SPACE_TEXTURE))
		return (-1);
	i = 0;
	while (i < 8)
	{
		path = build_door_path(i);
		if (!check_valid_file_path(path))
		{
			cleanup_door_frames(game);
			ft_safefree((void **)&path);
			return (-1);
		}
		if (!load_door_texture(game, path, i))
		{
			cleanup_door_frames(game);
			ft_safefree((void **)&path);
			return (-1);
		}
		ft_safefree((void **)&path);
		i++;
	}
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
	{
		ft_fprintf(2, "Error: Invalid or inaccessible map file path\n");
		return (1);
	}
	alloc_and_init_all(&game);
	if (parser(map_path, game) < 0)
	{
		cleanup_early(game, map_path);
		exit(EXIT_FAILURE);
	}
	init_game(game, map_path);
	ft_safefree((void **)&map_path);
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
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		cleanup_early(game, map_path);
		exit(EXIT_FAILURE);
	}
	if (populate_map_array(map_path, game) < 0)
	{
		cleanup_later(game, map_path);
		exit(EXIT_FAILURE);
	}
	if (!is_valid_path(game, game->map.player_y, game->map.player_x))
	{
		ft_fprintf(2, "Error: Player has no valid path\n");
		cleanup_later(game, map_path);
		exit(EXIT_FAILURE);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1920, 1080, "cub3D");
	if (!game->win_ptr)
	{
		cleanup_later(game, map_path);
		exit(EXIT_FAILURE);
	}
	find_player_position(game);
}

/*
Initialises the game state and loads all required textures
*/
void	init_game(t_game *game, const char *map_file)
{
	init_mlx_sys(game, map_file);
	if (load_mlx_textures(game) < 0)
	{
		cleanup_later(game, map_file);
		exit(EXIT_FAILURE);
	}
	init_doors_from_map(game);
	if (setup_minimap(game) < 0)
	{
		cleanup_later(game, map_file);
		exit(EXIT_FAILURE);
	}
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, MAX_WIDTH, MAX_HEIGHT);
	if (!game->img.img_ptr)
	{
		cleanup_later(game, map_file);
		exit(EXIT_FAILURE);
	}
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
			&game->img.line_len, &game->img.endian);
}
