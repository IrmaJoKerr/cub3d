/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 08:19:21 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 06:27:00 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int	handle_keypress(int keycode, t_game *game);
int	handle_keyrelease(int keycode, t_game *game);
int	handle_window_close(t_game *game);
int	setup_event_hooks(t_game *game);

/*
Key event handler for all key presses
This function is called on KeyPress events
*/
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape || keycode == 0xff1b)
	{
		ft_fprintf(2, "ESC key pressed - Initiating clean exit...\n");
		cleanup(game);
		exit(EXIT_SUCCESS);
	}
	if (handle_movement_keys(keycode, game))
		return (0);
	if (handle_rotation_keys(keycode, game))
		return (0);
	return (0);
}

/*
Key event handler for key release events
This function is called on KeyRelease events
*/
int	handle_keyrelease(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	return (0);
}

/*
Window close event handler for X button clicks
This function is called when user clicks the X button
*/
int	handle_window_close(t_game *game)
{
	ft_fprintf(2, "Window close button clicked - Initiating clean exit...\n");
	cleanup(game);
	exit(EXIT_SUCCESS);
}

int	setup_event_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse_move, game);
	mlx_hook(game->win_ptr, 17, 1L << 17, handle_window_close, game);
	return (0);
}
