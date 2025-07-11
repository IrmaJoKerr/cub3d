/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:55:10 by bleow             #+#    #+#             */
/*   Updated: 2025/07/11 08:45:39 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		is_valid_path(t_game *game, int y, int x);

/*
Recursive function to check if player has access to at least one empty space
or door.
Only needs to find one adjacent '0' or 'D' to be valid.
Returns 1 if found, 0 if not found.
*/
int	is_valid_path(t_game *game, int y, int x)
{
	if (y < 0 || y >= game->map.max_rows || x < 0 || x >= game->map.max_cols)
		return (0);
	if ((game->map.map[y][x] == '0') || (game->map.map[y][x] == 'D'))
		return (1);
	if (game->map.map[y][x] == '1')
		return (0);
	if ((y == game->map.player_y && x == game->map.player_x))
	{
		if (is_valid_path(game, y - 1, x))
			return (1);
		if (is_valid_path(game, y + 1, x))
			return (1);
		if (is_valid_path(game, y, x - 1))
			return (1);
		if (is_valid_path(game, y, x + 1))
			return (1);
	}
	return (0);
}
