/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_look.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 06:17:54 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 06:22:58 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int	handle_rotation_keys(int keycode, t_game *game);
int	press_left(t_game *game);
int	press_right(t_game *game);
int	press_up(t_game *game);
int	press_down(t_game *game);

/*
Handle arrow key rotation/looking
Returns 1 if rotation key was processed, 0 otherwise
*/
int	handle_rotation_keys(int keycode, t_game *game)
{
	if (keycode == XK_Left || keycode == 0xff51)
		return (press_left(game));
	else if (keycode == XK_Right || keycode == 0xff53)
		return (press_right(game));
	else if (keycode == XK_Up || keycode == 0xff52)
		return (press_up(game));
	else if (keycode == XK_Down || keycode == 0xff54)
		return (press_down(game));
	return (0);
}

// int	handle_rotation_keys(int keycode, t_game *game)
// {
// 	if (keycode == XK_Left || keycode == 0xff51)
// 	{
// 		game->view_direction += ROTATE_SPEED;
// 		game->view_direction = normalize_angle(game->view_direction);
// 		return (1);
// 	}
// 	else if (keycode == XK_Right || keycode == 0xff53)
// 	{
// 		game->view_direction -= ROTATE_SPEED;
// 		game->view_direction = normalize_angle(game->view_direction);
// 		return (1);
// 	}
// 	else if (keycode == XK_Up || keycode == 0xff52)
// 	{
// 		game->view_elevation += 10;
// 		game->view_elevation = clamp_elevation(game->view_elevation);
// 		calc_midline(game);
// 		return (1);
// 	}
// 	else if (keycode == XK_Down || keycode == 0xff54)
// 	{
// 		game->view_elevation -= 10;
// 		game->view_elevation = clamp_elevation(game->view_elevation);
// 		calc_midline(game);
// 		return (1);
// 	}
// 	return (0);
// }

/*
Looks left (Left arrow key)
*/
int	press_left(t_game *game)
{
	game->view_direction += ROTATE_SPEED;
	game->view_direction = normalize_angle(game->view_direction);
	return (1);
}

/*
Looks right (Right arrow key)
*/
int	press_right(t_game *game)
{
	game->view_direction -= ROTATE_SPEED;
	game->view_direction = normalize_angle(game->view_direction);
	return (1);
}

/*
Looks up (Up arrow key)
*/
int	press_up(t_game *game)
{
	game->view_elevation += 10;
	game->view_elevation = clamp_elevation(game->view_elevation);
	calc_midline(game);
	return (1);
}

/*
Looks down (Down arrow key)
*/
int	press_down(t_game *game)
{
	game->view_elevation -= 10;
	game->view_elevation = clamp_elevation(game->view_elevation);
	calc_midline(game);
	return (1);
}
