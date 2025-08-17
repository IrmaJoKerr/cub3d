/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 00:17:40 by wjun-kea          #+#    #+#             */
/*   Updated: 2025/08/17 10:22:22 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycasting.h"

static void	update_door_state(t_game *game, t_door *door)
{
	double	dx;
	double	dy;
	double	dist_sq;
	bool	near_enough;

	dx = door->x - game->curr_x;
	dy = door->y - game->curr_y;
	dist_sq = dx * dx + dy * dy;
	near_enough = dist_sq < 7.0;
	if (door->state == DOOR_CLOSED && near_enough)
		door->state = DOOR_OPENING;
	else if (door->state == DOOR_OPEN && !near_enough)
		door->state = DOOR_CLOSING;
}

static void	update_door_animation(t_game *game, t_door *door)
{
	if (door->state == DOOR_OPENING)
	{
		door->openness += DOOR_ANIM_SPEED;
		if (door->openness >= 1.0)
		{
			door->openness = 1.0;
			door->state = DOOR_OPEN;
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->openness -= DOOR_ANIM_SPEED;
		if (door->openness <= 0.0)
		{
			door->openness = 0.0;
			door->state = DOOR_CLOSED;
		}
	}
	door->animation_frame = (int)(door->openness
			* (game->textures.door_frame_count - 1));
}

void	update_doors(t_game *game)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < game->doorcount)
	{
		door = &game->doors[i];
		update_door_state(game, door);
		update_door_animation(game, door);
		i++;
	}
}

static bool	check_tile_hit(t_ray *wall_ray, t_ray *door_ray,
	t_game *game, bool *door_found)
{
	char	tile;

	tile = game->map.map[wall_ray->map_y][wall_ray->map_x];
	if (!*door_found && (tile == DOOR))
	{
		*door_ray = *wall_ray;
		door_ray->hit = 1;
		door_ray->hit_tile = tile;
		*door_found = true;
	}
	if (tile == TILE_WALL)
	{
		wall_ray->hit = 1;
		wall_ray->hit_tile = tile;
		return (true);
	}
	return (false);
}

void	perform_dda_with_door(t_ray *wall_ray,
	t_ray *door_ray, t_game *game)
{
	bool	door_found;

	door_found = false;
	while (1)
	{
		if (wall_ray->side_x < wall_ray->side_y)
		{
			wall_ray->side_x += wall_ray->delta_x;
			wall_ray->map_x += wall_ray->step_x;
			wall_ray->side = 0;
		}
		else
		{
			wall_ray->side_y += wall_ray->delta_y;
			wall_ray->map_y += wall_ray->step_y;
			wall_ray->side = 1;
		}
		if (check_tile_hit(wall_ray, door_ray, game, &door_found))
			break ;
	}
}
