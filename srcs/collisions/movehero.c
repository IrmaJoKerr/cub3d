/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movehero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:51:22 by bleow             #+#    #+#             */
/*   Updated: 2025/07/16 15:40:36 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Helper function to check for collisions between the hero sprite
and other sprites using the distance calculation function.
*/
int	is_collision(double player_x, double player_y, double obj_x, double obj_y)
{
	double	distance;

	// Calculate distance using our tile calculation function
	distance = calc_distance(player_x, player_y, obj_x, obj_y);
	
	// Return true if within collision radius
	return (distance < PLAYER_RADIUS);
}
