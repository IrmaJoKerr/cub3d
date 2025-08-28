/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:45:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/27 03:48:04 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
double	calc_move_dx(double view_direction, double speed, int forward);
double	calc_move_dy(double view_direction, double speed, int forward);
double	calc_strafe_dx(double view_direction, double speed, int right);
double	calc_strafe_dy(double view_direction, double speed, int right);

/*
Calculate movement delta X for forward/backward movement
*/
double	calc_move_dx(double view_direction, double speed, int forward)
{
	if (forward)
		return (cos(view_direction) * speed);
	else
		return (-cos(view_direction) * speed);
}

/*
Calculate movement delta Y for forward/backward movement
*/
double	calc_move_dy(double view_direction, double speed, int forward)
{
	if (forward)
		return (sin(view_direction) * speed);
	else
		return (-sin(view_direction) * speed);
}

/*
Calculate strafe delta X for left/right movement
*/
double	calc_strafe_dx(double view_direction, double speed, int right)
{
	if (right)
		return (sin(view_direction) * speed);
	else
		return (-sin(view_direction) * speed);
}

/*
Calculate strafe delta Y for left/right movement
*/
double	calc_strafe_dy(double view_direction, double speed, int right)
{
	if (right)
		return (-cos(view_direction) * speed);
	else
		return (cos(view_direction) * speed);
}
