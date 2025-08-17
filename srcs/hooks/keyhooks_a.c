/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 08:19:21 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 10:40:02 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include <X11/keysym.h>

/*
Function prototypes
*/
int	handle_movement_keys(int keycode, t_game *game);
int	handle_rotation_keys(int keycode, t_game *game);
int	handle_keypress(int keycode, t_game *game);
int	handle_keyrelease(int keycode, t_game *game);
int	handle_window_close(t_game *game);
int	handle_mouse_move(int x, int y, t_game *game);
int	setup_event_hooks(t_game *game);

/*
Handle WASD movement keys
Returns 1 if movement key was processed, 0 otherwise
*/
int	handle_movement_keys(int keycode, t_game *game)
{
	double	new_x;
	double	new_y;
	double	dx;
	double	dy;

	if (keycode == XK_w || keycode == 119)
	{
		dx = calc_move_dx(game->view_direction, MOVE_SPEED, 1);
		dy = calc_move_dy(game->view_direction, MOVE_SPEED, 1);
		new_x = game->curr_x + dx;
		new_y = game->curr_y + dy;
		if (is_valid_world_position(game, new_x, new_y))
		{	
			game->curr_x = new_x;
			game->curr_y = new_y;
			fprintf(stdout, "W key: Moving forward to (%.2f, %.2f) "
				"- tile (%d, %d)\n", new_x, new_y, world_to_tile_x(new_x),
				world_to_tile_y(new_y));
		}
		else
			fprintf(stdout, "W key: Movement blocked by wall at tile (%d, %d)\n",
				world_to_tile_x(new_x), world_to_tile_y(new_y));
		(void)game;
		return (1);
	}
	else if (keycode == XK_s || keycode == 115)
	{
		dx = calc_move_dx(game->view_direction, MOVE_SPEED, 0);
		dy = calc_move_dy(game->view_direction, MOVE_SPEED, 0);
		new_x = game->curr_x + dx;
		new_y = game->curr_y + dy;
		
		if (is_valid_world_position(game, new_x, new_y))
		{
			game->curr_x = new_x;
			game->curr_y = new_y;
			fprintf(stdout, "S key: Moving backward to (%.2f, %.2f) - tile (%d, %d)\n", 
				new_x, new_y, world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
		else
			fprintf(stdout, "S key: Movement blocked by wall at tile (%d, %d)\n",
				world_to_tile_x(new_x), world_to_tile_y(new_y));
		(void)game;
		return (1);
	}
	else if (keycode == XK_a || keycode == 97)
	{
		dx = calc_strafe_dx(game->view_direction, MOVE_SPEED, 0);
		dy = calc_strafe_dy(game->view_direction, MOVE_SPEED, 0);
		new_x = game->curr_x + dx;
		new_y = game->curr_y + dy;
		
		if (is_valid_world_position(game, new_x, new_y))
		{
			game->curr_x = new_x;
			game->curr_y = new_y;
			fprintf(stdout, "A key: Strafing left to (%.2f, %.2f) - tile (%d, %d)\n", 
				new_x, new_y, world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
		else
			fprintf(stdout, "A key: Movement blocked by wall at tile (%d, %d)\n",
				world_to_tile_x(new_x), world_to_tile_y(new_y));
		(void)game;
		return (1);
	}
	else if (keycode == XK_d || keycode == 100)
	{
		dx = calc_strafe_dx(game->view_direction, MOVE_SPEED, 1);
		dy = calc_strafe_dy(game->view_direction, MOVE_SPEED, 1);
		new_x = game->curr_x + dx;
		new_y = game->curr_y + dy;
		
		if (is_valid_world_position(game, new_x, new_y))
		{
			game->curr_x = new_x;
			game->curr_y = new_y;
			fprintf(stdout, "D key: Strafing right to (%.2f, %.2f) - tile (%d, %d)\n", 
				new_x, new_y, world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
		else
			fprintf(stdout, "D key: Movement blocked by wall at tile (%d, %d)\n",
				world_to_tile_x(new_x), world_to_tile_y(new_y));
		(void)game;
		return (1);
	}
	return (0);
}

/*
Handle arrow key rotation/looking
Returns 1 if rotation key was processed, 0 otherwise
*/
int	handle_rotation_keys(int keycode, t_game *game)
{
	if (keycode == XK_Left || keycode == 0xff51)
	{
		game->view_direction += ROTATE_SPEED;
		game->view_direction = normalize_angle(game->view_direction);
		fprintf(stdout, "Left Arrow: Looking left (angle: %.3f radians)\n", game->view_direction);
		return (1);
	}
	else if (keycode == XK_Right || keycode == 0xff53)
	{
		game->view_direction -= ROTATE_SPEED;
		game->view_direction = normalize_angle(game->view_direction);
		fprintf(stdout, "Right Arrow: Looking right (angle: %.3f radians)\n", game->view_direction);
		return (1);
	}
	else if (keycode == XK_Up || keycode == 0xff52)
	{
		game->view_elevation += 10;
		game->view_elevation = clamp_elevation(game->view_elevation);
		fprintf(stdout, "Up Arrow: Looking up (elevation: %.3f radians)\n", game->view_elevation);
		return (1);
	}
	else if (keycode == XK_Down || keycode == 0xff54)
	{
		game->view_elevation -= 10;
		game->view_elevation = clamp_elevation(game->view_elevation);
		fprintf(stdout, "Down Arrow: Looking down (elevation: %.3f radians)\n", game->view_elevation);
		return (1);
	}
	return (0);
}

/*
Key event handler for all key presses
This function is called on KeyPress events
*/
int	handle_keypress(int keycode, t_game *game)
{
	fprintf(stdout, "DEBUG: Keycode pressed: %d (0x%x)\n", keycode, keycode);
	if (keycode == XK_Escape || keycode == 0xff1b)
	{
		fprintf(stdout, "ESC key pressed - Initiating clean exit...\n");
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
	fprintf(stdout, "Window close button clicked - Initiating clean exit...\n");
	cleanup(game);
	exit(EXIT_SUCCESS);
}

/*
Initialize all event hooks for the game window
Sets up WASD movement, arrow key rotation, ESC exit, and window close handlers
*/

int handle_mouse_move(int x, int y, t_game *game)
{
	static int prev_x = -1;
	static int prev_y = -1;
	int center_x = MAX_WIDTH / 2;
	int center_y = MAX_HEIGHT / 2;

	// Ignore first call
	if (prev_x == -1 || prev_y == -1)
	{
		prev_x = x;
		prev_y = y;
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center_x, center_y);
		return (0);
	}

	int delta_x = x - center_x;
	int delta_y = y - center_y;
	if (delta_x != 0 || delta_y != 0)
	{
		game->view_direction -= delta_x * MOUSE_SENSITIVITY;
		game->view_direction = normalize_angle(game->view_direction);
		game->view_elevation -= delta_y * MOUSE_SENSITIVITY * 180;
		game->view_elevation = clamp_elevation(game->view_elevation);
		mlx_mouse_move(game->mlx_ptr, game->win_ptr, center_x, center_y);
	}
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	prev_x = x;
	prev_y = y;
	return (0);
}

int	setup_event_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L<<0, handle_keypress, game);
	mlx_hook(game->win_ptr, 3, 1L<<1, handle_keyrelease, game);
	mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse_move, game);
	mlx_hook(game->win_ptr, 17, 1L<<17, handle_window_close, game);
	return (0);
}

