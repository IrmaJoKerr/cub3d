/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:29:37 by bleow             #+#    #+#             */
/*   Updated: 2025/07/11 10:22:49 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <wchar.h>

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
		ft_printf("Error: \n");
		ft_printf("Failed to allocate memory for map path.\n");
		return (NULL);
	}
	if (!chk_valid_path(full_path))
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

int	chk_valid_path(const char *full_path)
{
	int		fd;

	fd = open(full_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: \n");
		ft_printf("Map file '%s' does not exist.\n", full_path);
		return (0);
	}
	close(fd);
	return (1);
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
