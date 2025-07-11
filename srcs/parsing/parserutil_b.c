/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserutil_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:05:51 by bleow             #+#    #+#             */
/*   Updated: 2025/07/11 22:23:23 by wjun-kea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
		ft_fprintf(2, "Player start point in map does not exist or too many. \n");
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
*/
int	check_map_validity(t_game *game)
{
	if (!check_counts(game))
		return (0);
	if (!is_valid_path(game, game->map.player_y, game->map.player_x))
	{
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Player has no valid path to empty spaces.\n");
		return (0);
	}
	return (1);
}
