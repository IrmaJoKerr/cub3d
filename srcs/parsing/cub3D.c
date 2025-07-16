/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:29:37 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 10:12:10 by bleow            ###   ########.fr       */
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
}
