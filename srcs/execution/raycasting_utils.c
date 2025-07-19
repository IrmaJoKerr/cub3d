#include "../includes/raycasting.h"

// Function to initialize the ray structure with camera position, direction, and deltas

void init_ray(t_ray *ray, t_game *game, int x)
{
	ray->cam_x = 2.0 * x / MAX_WIDTH - 1.0;
	ray->dir_x = cos(game->view_direction) + (sin(game->view_direction) * tan(FOV / 2)) * ray->cam_x;
	ray->dir_y = sin(game->view_direction) - (cos(game->view_direction) * tan(FOV / 2)) * ray->cam_x;
	ray->map_x = (int)(game->curr_x);
	ray->map_y = (int)(game->curr_y);
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->dir_y);
	initialize_deltas_and_steps(ray, game);
	ray->hit = 0;
}

// Function to put a pixel on the image at (x, y) with the specified color
void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= MAX_WIDTH || y < 0 || y >= MAX_HEIGHT)
 		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// Function to fill the sky and floor with their respective colors
void	fill_sky_and_floor(t_game *game)
{
	int	sky_color;
	int	floor_color;
	int	y;
	int	x;
	int	midline;

	y = 0;
	sky_color = (game->map.sky_color[0] << 16) | (game->map.sky_color[1] << 8) | game->map.sky_color[2];
	floor_color = (game->map.floor_color[0] << 16) | (game->map.floor_color[1] << 8) | game->map.floor_color[2];
	midline = MAX_HEIGHT / 2 + game->view_elevation;
	if (midline < 0)
		midline = 0;
	if (midline > MAX_HEIGHT)
		midline = MAX_HEIGHT;
	while (y < MAX_HEIGHT)
	{
		x = 0;
		while (x < MAX_WIDTH)
		{
			if (y < midline)
				put_pixel(&game->img, x, y, sky_color);
			else
				put_pixel(&game->img, x, y, floor_color);
			++x;
		}
		++y;
	}
}

// Function to get the appropriate wall texture based on the ray's side and direction

t_image	*get_wall_texture(t_game *game, int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x < 0)
			return game->textures.west_wall;
		else
			return game->textures.east_wall;
	}
	else
	{
		if (ray_dir_y < 0)
			return game->textures.north_wall;
		else
			return game->textures.south_wall;
	}			
}

// Function to initialize deltas and steps based on ray direction and current position

void	initialize_deltas_and_steps(t_ray *ray, t_game *game)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->curr_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->curr_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->curr_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->curr_y) * ray->delta_y;
	}
}
