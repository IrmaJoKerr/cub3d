/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserutil_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:05:51 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 09:34:40 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_counts(t_game *game);
int	check_map_validity(t_game *game);

/*
Checks if the map is surrounded by walls and if the herocount
is acceptable.
*/
int	check_counts(t_game *game)
{
	if (game->map.herocount != 1)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Player start point in map \n");
		ft_fprintf(2, "does not exist or too many.\n");
		return (0);
	}
	if (!game->map.map_first_wall)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "First line must be all walls ('1').\n");
		return (0);
	}
	if (!game->map.map_last_wall)
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Last line must be all walls ('1').\n");
		return (0);
	}
	return (1);
}

/*
Checks if the map pathing is valid. Validates map size and counts.
Enhanced with detailed error reporting for flood fill validation failures.
*/
int	check_map_validity(t_game *game)
{
	if (!check_counts(game))
		return (0);
	
	printf("DEBUG: Starting enhanced flood fill path validation...\n");
	if (!is_valid_path(game, game->map.player_y, game->map.player_x))
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Enhanced validation failed: Player can reach map boundaries.\n");
		ft_fprintf(2, "This creates a security vulnerability - map is not properly enclosed.\n");
		ft_fprintf(2, "Ensure all reachable areas are surrounded by walls ('1').\n");
		return (0);
	}
	
	printf("DEBUG: Enhanced flood fill validation completed successfully\n");
	return (1);
}
