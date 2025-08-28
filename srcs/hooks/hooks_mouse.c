/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 06:26:10 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 16:33:44 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		handle_mouse_move(int x, int y, t_game *game);
void	mouse_delta_calc(int x, int y, t_game *game);

/*
Handles mouse movement events
*/
int	handle_mouse_move(int x, int y, t_game *game)
{
	static int	prev_x;
	static int	prev_y;
	static int	init;

	if (!init)
	{
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, (MAX_WIDTH / 2),
			(MAX_HEIGHT / 2));
		prev_x = -1;
		prev_y = -1;
		init = 1;
	}
	if (prev_x == -1 || prev_y == -1)
	{
		prev_x = x;
		prev_y = y;
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, (MAX_WIDTH / 2),
			(MAX_HEIGHT / 2));
		return (0);
	}
	mouse_delta_calc(x, y, game);
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	prev_x = x;
	prev_y = y;
	return (0);
}

/*
Calculates mouse movement delta and updates view direction/elevation
*/
void	mouse_delta_calc(int x, int y, t_game *game)
{
	int	delta_x;
	int	delta_y;

	delta_x = x - (MAX_WIDTH / 2);
	delta_y = y - (MAX_HEIGHT / 2);
	if (delta_x != 0 || delta_y != 0)
	{
		game->view_direction -= delta_x * 0.000029;
		game->view_direction = normalize_angle(game->view_direction);
		game->view_elevation -= delta_y * (0.00029 * 180);
		game->view_elevation = clamp_elevation(game->view_elevation);
		calc_midline(game);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, (MAX_WIDTH / 2),
			(MAX_HEIGHT / 2));
	}
}
