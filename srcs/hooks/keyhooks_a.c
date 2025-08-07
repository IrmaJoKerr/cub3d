/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 08:19:21 by bleow             #+#    #+#             */
/*   Updated: 2025/08/07 16:42:17 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include <X11/keysym.h>

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
		
		printf("🔸 PLAYER MOVEMENT [W]: Current pos (%.2f, %.2f) -> target (%.2f, %.2f) [deltas: (%.4f, %.4f)]\n",
			game->curr_x, game->curr_y, new_x, new_y, dx, dy);
		
		if (is_valid_world_position(game, new_x, new_y))
		{		
			game->curr_x = new_x;
			game->curr_y = new_y;
			game->needs_render = true;  // Mark for re-render
			fprintf(stdout, "✅ W key: MOVED to (%.2f, %.2f) - tile (%d, %d) | Distance: %.3f units\n", 
				new_x, new_y, world_to_tile_x(new_x), world_to_tile_y(new_y),
				sqrt(dx*dx + dy*dy));
		}
		else
		{
			store_door_attempt(game, new_x, new_y);  // Store for door trigger
			fprintf(stdout, "❌ W key: Movement BLOCKED by wall at tile (%d, %d)\n",
				world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
		(void)game;
		return (1);
	}
	else if (keycode == XK_s || keycode == 115)
	{
		dx = calc_move_dx(game->view_direction, MOVE_SPEED, 0);
		dy = calc_move_dy(game->view_direction, MOVE_SPEED, 0);
		new_x = game->curr_x + dx;
		new_y = game->curr_y + dy;
		
		printf("🔸 PLAYER MOVEMENT [S]: Current pos (%.2f, %.2f) -> target (%.2f, %.2f) [deltas: (%.4f, %.4f)]\n",
			game->curr_x, game->curr_y, new_x, new_y, dx, dy);
		
		if (is_valid_world_position(game, new_x, new_y))
		{
			game->curr_x = new_x;
			game->curr_y = new_y;
			game->needs_render = true;  // Mark for re-render
			fprintf(stdout, "✅ S key: MOVED to (%.2f, %.2f) - tile (%d, %d)\n", 
				new_x, new_y, world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
		else
		{
			store_door_attempt(game, new_x, new_y);  // Store for door trigger
			fprintf(stdout, "❌ S key: Movement BLOCKED by wall at tile (%d, %d)\n",
				world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
		(void)game;
		return (1);
	}
	else if (keycode == XK_a || keycode == 97)
	{
		dx = calc_strafe_dx(game->view_direction, MOVE_SPEED, 0);
		dy = calc_strafe_dy(game->view_direction, MOVE_SPEED, 0);
		new_x = game->curr_x + dx;
		new_y = game->curr_y + dy;
		
		printf("🔸 PLAYER MOVEMENT [A]: Current pos (%.2f, %.2f) -> target (%.2f, %.2f) [deltas: (%.4f, %.4f)]\n",
			game->curr_x, game->curr_y, new_x, new_y, dx, dy);
		
		if (is_valid_world_position(game, new_x, new_y))
		{
			game->curr_x = new_x;
			game->curr_y = new_y;
			game->needs_render = true;  // Mark for re-render
			fprintf(stdout, "✅ A key: STRAFED LEFT to (%.2f, %.2f) - tile (%d, %d)\n", 
				new_x, new_y, world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
		else
		{
			store_door_attempt(game, new_x, new_y);  // Store for door trigger
			fprintf(stdout, "❌ A key: Strafe BLOCKED by wall at tile (%d, %d)\n",
				world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
		(void)game;
		return (1);
	}
	else if (keycode == XK_d || keycode == 100)
	{
		dx = calc_strafe_dx(game->view_direction, MOVE_SPEED, 1);
		dy = calc_strafe_dy(game->view_direction, MOVE_SPEED, 1);
		new_x = game->curr_x + dx;
		new_y = game->curr_y + dy;
		
		printf("🔸 PLAYER MOVEMENT [D]: Current pos (%.2f, %.2f) -> target (%.2f, %.2f) [deltas: (%.4f, %.4f)]\n",
			game->curr_x, game->curr_y, new_x, new_y, dx, dy);
		
		if (is_valid_world_position(game, new_x, new_y))
		{
			game->curr_x = new_x;
			game->curr_y = new_y;
			game->needs_render = true;  // Mark for re-render
			fprintf(stdout, "✅ D key: STRAFED RIGHT to (%.2f, %.2f) - tile (%d, %d)\n", 
				new_x, new_y, world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
		else
		{
			store_door_attempt(game, new_x, new_y);  // Store for door trigger
			fprintf(stdout, "❌ D key: Strafe BLOCKED by wall at tile (%d, %d)\n",
				world_to_tile_x(new_x), world_to_tile_y(new_y));
		}
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
		game->view_direction -= ROTATE_SPEED;
		game->view_direction = normalize_angle(game->view_direction);
		game->needs_render = true;  // Mark for re-render
		fprintf(stdout, "🔄 Left Arrow: View angle changed to %.3f radians (%.1f degrees)\n", 
			game->view_direction, game->view_direction * 180.0 / M_PI);
		return (1);
	}
	else if (keycode == XK_Right || keycode == 0xff53)
	{
		game->view_direction += ROTATE_SPEED;
		game->view_direction = normalize_angle(game->view_direction);
		game->needs_render = true;  // Mark for re-render
		fprintf(stdout, "🔄 Right Arrow: View angle changed to %.3f radians (%.1f degrees)\n", 
			game->view_direction, game->view_direction * 180.0 / M_PI);
		return (1);
	}
	else if (keycode == XK_Up || keycode == 0xff52)
	{
		game->view_elevation += ELEVATION_SPEED;
		if (game->view_elevation > MAX_ELEVATION)
			game->view_elevation = MAX_ELEVATION;
		game->needs_render = true;  // Mark for re-render
		fprintf(stdout, "🔼 Up Arrow: Looking up (elevation: %.3f radians, %.1f degrees)\n", 
			game->view_elevation, game->view_elevation * 180.0 / M_PI);
		return (1);
	}
	else if (keycode == XK_Down || keycode == 0xff54)
	{
		game->view_elevation -= ELEVATION_SPEED;
		if (game->view_elevation < -MAX_ELEVATION)
			game->view_elevation = -MAX_ELEVATION;
		game->needs_render = true;  // Mark for re-render
		fprintf(stdout, "🔽 Down Arrow: Looking down (elevation: %.3f radians, %.1f degrees)\n", 
			game->view_elevation, game->view_elevation * 180.0 / M_PI);
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
	// fprintf(stdout, "DEBUG: Keycode pressed: %d (0x%x)\n", keycode, keycode);
	if (keycode == XK_Escape || keycode == 0xff1b)
	{
		fprintf(stdout, "🚪 ESC key pressed - Initiating clean exit...\n");
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
int	setup_event_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L<<0, handle_keypress, game);
	mlx_hook(game->win_ptr, 3, 1L<<1, handle_keyrelease, game);
	mlx_hook(game->win_ptr, 17, 1L<<17, handle_window_close, game);
	return (0);
}

