/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 06:03:28 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 06:16:40 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int	handle_movement_keys(int keycode, t_game *game);
int	press_w(t_game *game);
int	press_s(t_game *game);
int	press_a(t_game *game);
int	press_d(t_game *game);

/*
Handle WASD movement keys
Returns 1 if movement key was processed, 0 otherwise
*/
int	handle_movement_keys(int keycode, t_game *game)
{
	if (keycode == XK_w || keycode == 119)
		return (press_w(game));
	else if (keycode == XK_s || keycode == 115)
		return (press_s(game));
	else if (keycode == XK_a || keycode == 97)
		return (press_a(game));
	else if (keycode == XK_d || keycode == 100)
		return (press_d(game));
	return (0);
}

/*
Moves forward (W key)
*/
int	press_w(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->curr_x + calc_move_dx(game->view_direction, MOVE_SPEED, 1);
	new_y = game->curr_y + calc_move_dy(game->view_direction, MOVE_SPEED, 1);
	if (is_valid_move(game, new_x, new_y))
	{
		game->curr_x = new_x;
		game->curr_y = new_y;
	}
	else
		ft_fprintf(2, "W key: Movement blocked at tile (%d, %d)\n",
			world_to_tile_x(new_x), world_to_tile_y(new_y));
	return (1);
}

/*
Moves backward (S key)
*/
int	press_s(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->curr_x + calc_move_dx(game->view_direction, MOVE_SPEED, 0);
	new_y = game->curr_y + calc_move_dy(game->view_direction, MOVE_SPEED, 0);
	if (is_valid_move(game, new_x, new_y))
	{
		game->curr_x = new_x;
		game->curr_y = new_y;
	}
	else
		fprintf(stdout, "S key: Movement blocked at tile (%d, %d)\n",
			world_to_tile_x(new_x), world_to_tile_y(new_y));
	return (1);
}

/*
Strafes left (A key)
*/
int	press_a(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->curr_x + calc_strafe_dx(game->view_direction, MOVE_SPEED, 0);
	new_y = game->curr_y + calc_strafe_dy(game->view_direction, MOVE_SPEED, 0);
	if (is_valid_move(game, new_x, new_y))
	{
		game->curr_x = new_x;
		game->curr_y = new_y;
	}
	else
		ft_fprintf(2, "A key: Movement blocked at tile (%d, %d)\n",
			world_to_tile_x(new_x), world_to_tile_y(new_y));
	return (1);
}

/*
Strafes right (D key)
*/
int	press_d(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->curr_x + calc_strafe_dx(game->view_direction, MOVE_SPEED, 1);
	new_y = game->curr_y + calc_strafe_dy(game->view_direction, MOVE_SPEED, 1);
	if (is_valid_move(game, new_x, new_y))
	{
		game->curr_x = new_x;
		game->curr_y = new_y;
	}
	else
		ft_fprintf(2, "D key: Movement blocked at tile (%d, %d)\n",
			world_to_tile_x(new_x), world_to_tile_y(new_y));
	return (1);
}
