/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/07 15:41:55 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Update all door animations
*/
void	update_door_animations(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->doorcount)
	{
		update_single_door(game, &game->doors[i]);
		i++;
	}
}

/*
Update individual door state and animation - simplified
*/
void	update_single_door(t_game *game, t_door *door)
{
	double	player_distance;
	double	door_center_x;
	double	door_center_y;
	double	proximity_threshold;
	int		player_near;
	static int debug_counter = 0;

	door_center_x = tile_center_x(door->x);
	door_center_y = tile_center_y(door->y);
	proximity_threshold = DOOR_PROXIMITY_TILES * TILE_SIZE;
	
	player_distance = calc_distance(game->curr_x, game->curr_y, 
									door_center_x, door_center_y);
	player_near = (player_distance <= proximity_threshold);
	
	// Debug: Print door status every 100 frames for each door to avoid spam
	if (debug_counter % 100 == 0 && player_distance < 200.0)
	{
		printf("🚪 DOOR DEBUG [%c at (%d,%d)]: Player at (%.1f,%.1f), Door center (%.1f,%.1f), Distance: %.1f, Threshold: %.1f, Near: %s, State: %d, Frame: %d\n",
			door->type, door->x, door->y, 
			game->curr_x, game->curr_y, door_center_x, door_center_y,
			player_distance, proximity_threshold, 
			player_near ? "YES" : "NO", door->state, door->animation_frame);
	}
	debug_counter++;
	
	if (door->state == DOOR_CLOSED)
	{
		// Open door when player is near, regardless of specific movement attempts
		if (player_near)
		{
			printf("🔓 OPENING DOOR [%c at (%d,%d)]: Player near door (proximity-based opening)!\n", 
				door->type, door->x, door->y);
			open_door(door);
		}
	}
	else if (door->state == DOOR_OPENING)
	{
		door->openness += DOOR_ANIM_SPEED;
		if (door->openness >= 1.0)
		{
			door->openness = 1.0;
			door->state = DOOR_OPEN;
			door->animation_frame = MAX_DOOR_FRAMES - 1;
			printf("🚪 DOOR FULLY OPENED [%c at (%d,%d)]: Animation complete!\n", 
				door->type, door->x, door->y);
		}
		else
		{
			door->animation_frame = (int)(door->openness * (MAX_DOOR_FRAMES - 1));
		}
	}
	else if (door->state == DOOR_OPEN)
	{
		if (!player_near)
		{
			printf("🔒 CLOSING DOOR [%c at (%d,%d)]: Player moved away!\n", 
				door->type, door->x, door->y);
			close_door(door);
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->openness -= DOOR_ANIM_SPEED;
		if (door->openness <= 0.0)
		{
			door->openness = 0.0;
			door->state = DOOR_CLOSED;
			door->animation_frame = 0;
		}
		else
		{
			door->animation_frame = (int)(door->openness * (MAX_DOOR_FRAMES - 1));
		}
	}
}

/*
Check if player is attempting to move into this specific door from a valid approach direction
*/
int	is_player_attempting_entry(t_game *game, t_door *door)
{
	long	current_time;
	int		target_tile_x;
	int		target_tile_y;
	int		from_tile_x;
	int		from_tile_y;
	int		is_attempting;
	int		is_valid_approach;
	
	(void)game;
	current_time = get_current_time_ms();
	if (current_time - door->last_attempt_time > 200)
		return (0);
	
	target_tile_x = world_to_tile_x(door->last_attempt_x);
	target_tile_y = world_to_tile_y(door->last_attempt_y);
	from_tile_x = world_to_tile_x(door->last_attempt_from_x);
	from_tile_y = world_to_tile_y(door->last_attempt_from_y);
	
	is_attempting = (target_tile_x == door->x && target_tile_y == door->y);
	
	// Check if approach direction is valid for this door type
	if (door->type == HORIZ_DOOR)
	{
		// Horizontal doors: valid if approaching from North (above) or South (below)
		is_valid_approach = (from_tile_y != target_tile_y) && (from_tile_x == target_tile_x);
	}
	else if (door->type == VERTI_DOOR)
	{
		// Vertical doors: valid if approaching from West (left) or East (right)
		is_valid_approach = (from_tile_x != target_tile_x) && (from_tile_y == target_tile_y);
	}
	else
	{
		is_valid_approach = 0;
	}
	
	if (is_attempting && is_valid_approach)
	{
		printf("🎯 DOOR ATTEMPT DETECTED [%c at (%d,%d)]: Valid approach from tile (%d,%d) to tile (%d,%d)\n",
			door->type, door->x, door->y, from_tile_x, from_tile_y, target_tile_x, target_tile_y);
	}
	else if (is_attempting && !is_valid_approach)
	{
		printf("🚫 DOOR ATTEMPT BLOCKED [%c at (%d,%d)]: Invalid approach from tile (%d,%d) - wrong direction for door type\n",
			door->type, door->x, door->y, from_tile_x, from_tile_y);
	}
	
	return (is_attempting && is_valid_approach);
}

/*
Store attempted movement position for specific door
*/
void	store_door_attempt(t_game *game, double x, double y)
{
	int		target_tile_x;
	int		target_tile_y;
	long	current_time;
	int		i;

	target_tile_x = world_to_tile_x(x);
	target_tile_y = world_to_tile_y(y);
	current_time = get_current_time_ms();

	printf("🚪 STORE DOOR ATTEMPT: Blocked movement to (%.1f,%.1f) targeting tile (%d,%d)\n", 
		x, y, target_tile_x, target_tile_y);

	i = 0;
	while (i < game->doorcount)
	{
		if (game->doors[i].x == target_tile_x && game->doors[i].y == target_tile_y)
		{
			game->doors[i].last_attempt_x = x;
			game->doors[i].last_attempt_y = y;
			game->doors[i].last_attempt_from_x = game->curr_x;
			game->doors[i].last_attempt_from_y = game->curr_y;
			game->doors[i].last_attempt_time = current_time;
			printf("🔑 DOOR ATTEMPT STORED [%c at (%d,%d)]: From current player pos (%.1f,%.1f) to (%.1f,%.1f) at time %ld\n",
				game->doors[i].type, game->doors[i].x, game->doors[i].y,
				game->curr_x, game->curr_y, x, y, current_time);
			break;
		}
		i++;
	}
}

/*
Start door opening animation
*/
void	open_door(t_door *door)
{
	door->state = DOOR_OPENING;
	door->openness = 0.0;
	door->animation_frame = 0;
}

/*
Start door closing animation
*/
void	close_door(t_door *door)
{
	door->state = DOOR_CLOSING;
}
