/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movehero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:51:22 by bleow             #+#    #+#             */
/*   Updated: 2025/07/11 08:45:40 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		is_collision(int player_x, int player_y, int obj_x, int obj_y);

/*
Helper function to check for collisions between the hero sprite
and other sprites.
*/
int	is_collision(int player_x, int player_y, int obj_x, int obj_y)
{
	return (player_x == obj_x && player_y == obj_y);
}
