/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserutil_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:05:51 by bleow             #+#    #+#             */
/*   Updated: 2025/07/05 15:38:24 by bleow            ###   ########.fr       */
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
		ft_printf("Error: \n");
		ft_printf("Player start point in map does not exist or too many. \n");
		return (0);
	}
	if (!game->map.map_first_wall)
	{
		ft_printf("Error: \n");
		ft_printf("First line must be all walls ('1').\n");
		return (0);
	}
	if (!game->map.map_last_wall)
	{
		ft_printf("Error: \n");
		ft_printf("Last line must be all walls ('1').\n");
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
	if (!is_valid_path(game, game->map.hero_y, game->map.hero_x))
	{
		ft_printf("Error: \n");
		ft_printf("Player has no valid path to empty spaces.\n");
		return (0);
	}
	return (1);
}
