/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 11:09:06 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 11:14:12 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
double	normalize_angle(double angle);
double	clamp_elevation(double elevation);

/*
Normalize angle to 0-2π range
*/
double	normalize_angle(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

/*
Clamp elevation angle to reasonable range (-π/2 to π/2)
*/
double	clamp_elevation(double elevation)
{
	if (elevation > 289)
		return (289);
	if (elevation < -289)
		return (-289);
	return (elevation);
}
