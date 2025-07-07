/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:29:37 by bleow             #+#    #+#             */
/*   Updated: 2025/07/05 12:51:12 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_game(t_game *game, const char *map_file);

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	alloc_and_init_all(&game);
	init_game(game, argv[1]);
	mlx_hook(game->win_ptr, 17, 0, close_window, game);
	mlx_loop(game->mlx_ptr);
	cleanup(game);
	return (0);
}

/*
Initialises the game window. Mark for refactoring.
Needs to free all memory allocated if the map init and validate fails
*/
void	init_game(t_game *game, const char *map_file)
{
	if (!parse_map(map_file, game))
	{
		ft_printf("Error: \n");
		ft_printf("Failed to parse and validate the map.\n");
		cleanup_early(game);
		exit(EXIT_FAILURE);
	}
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		ft_printf("Error: \n");
		ft_printf("Failed to initialize MiniLibX.\n");
		cleanup_early(game);
		exit(EXIT_FAILURE);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1920, 1080, "cub3D");
	if (!game->win_ptr)
	{
		ft_printf("Error: \n");
		ft_printf("Failed to create a new window.\n");
		cleanup_later(game);
		exit(EXIT_FAILURE);
	}
}
