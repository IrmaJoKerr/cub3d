/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:30:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/23 05:11:17 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	calculate_triangle_vertices(t_triangle *tri, t_point center,
			double angle);
void	get_y_bounds(t_triangle tri, int *min_y, int *max_y);
bool	get_scanline_segment(t_triangle tri, int y, int *x_start, int *x_end);
void	draw_scanline_segment(t_draw_info info, t_triangle tri, int y,
			int color);
void	rasterize_triangle(t_draw_info info, t_triangle tri);

/*
Calculate the vertices of the player indicator triangle on the minimap.
*/
void	calculate_triangle_vertices(t_triangle *tri,
	t_point center, double angle)
{
	double	left_angle;
	double	right_angle;

	left_angle = angle + 2.531;
	right_angle = angle - 2.531;
	tri->tip.x = center.x + (int)(cos(angle) * 6.0);
	tri->tip.y = center.y + (int)(sin(angle) * 6.0);
	tri->base_l.x = center.x + (int)(cos(left_angle) * 6.0);
	tri->base_l.y = center.y + (int)(sin(left_angle) * 6.0);
	tri->base_r.x = center.x + (int)(cos(right_angle) * 6.0);
	tri->base_r.y = center.y + (int)(sin(right_angle) * 6.0);
}

/*
Get the minimum and maximum y-coordinates of the triangle.
*/
void	get_y_bounds(t_triangle tri, int *min_y, int *max_y)
{
	*min_y = tri.tip.y;
	if (tri.base_l.y < *min_y)
		*min_y = tri.base_l.y;
	if (tri.base_r.y < *min_y)
		*min_y = tri.base_r.y;
	*max_y = tri.tip.y;
	if (tri.base_l.y > *max_y)
		*max_y = tri.base_l.y;
	if (tri.base_r.y > *max_y)
		*max_y = tri.base_r.y;
	if (*min_y < 0)
		*min_y = 0;
	if (*max_y >= 180)
		*max_y = 179;
}

/*
Find the x-coordinates of the scanline segment for a given y in the triangle.
*/
bool	get_scanline_segment(t_triangle tri, int y, int *x_start, int *x_end)
{
	t_point	vertices[3];
	int		i;
	t_point	p1;
	t_point	p2;
	double	x_intersect;

	vertices[0] = tri.tip;
	vertices[1] = tri.base_l;
	vertices[2] = tri.base_r;
	i = 0;
	while (i < 3)
	{
		p1 = vertices[i];
		p2 = vertices[(i + 1) % 3];
		if ((p1.y <= y && p2.y > y) || (p2.y <= y && p1.y > y))
		{
			x_intersect = p1.x + (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y);
			if (x_intersect < *x_start)
				*x_start = (int)x_intersect;
			if (x_intersect > *x_end)
				*x_end = (int)x_intersect;
		}
		i++;
	}
	return (*x_start <= *x_end);
}

/*
Draw a horizontal scanline segment for the triangle on the minimap.
*/
void	draw_scanline_segment(t_draw_info info,
	t_triangle tri, int y, int color)
{
	int	x_start;
	int	x_end;
	int	x;

	x_start = 180;
	x_end = -1;
	if (!get_scanline_segment(tri, y, &x_start, &x_end))
		return ;
	if (x_start < 0)
		x_start = 0;
	if (x_end >= 180)
		x_end = 179;
	x = x_start;
	while (x <= x_end)
	{
		info.pixels[y * info.stride + x] = color;
		x++;
	}
}

/*
Rasterize the triangle by drawing scanline segments between its bounds.
*/
void	rasterize_triangle(t_draw_info info, t_triangle tri)
{
	int	min_y;
	int	max_y;
	int	y;

	get_y_bounds(tri, &min_y, &max_y);
	y = min_y;
	while (y <= max_y)
	{
		draw_scanline_segment(info, tri, y, 0xFF4500);
		y++;
	}
}
