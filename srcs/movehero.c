/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movehero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:51:22 by bleow             #+#    #+#             */
/*   Updated: 2025/07/05 13:08:52 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		is_collision(int hero_x, int hero_y, int obj_x, int obj_y);

/*
Helper function to check for collisions between the hero sprite
and other sprites.
*/
int	is_collision(int hero_x, int hero_y, int obj_x, int obj_y)
{
	return (hero_x == obj_x && hero_y == obj_y);
}
