#include "../includes/raycasting.h"

// Function to initialize the ray structure with camera position, direction, and deltas

void init_ray(t_ray *ray, t_game *game, int x)
{
	double cam_dir_x, cam_dir_y, plane_x, plane_y;
	
	ray->cam_x = 2.0 * x / MAX_WIDTH - 1.0;
	
	// Calculate camera direction
	cam_dir_x = cos(game->view_direction);
	cam_dir_y = sin(game->view_direction);
	
	// Calculate camera plane (perpendicular to camera direction)
	plane_x = -cam_dir_y * tan(FOV / 2);
	plane_y = cam_dir_x * tan(FOV / 2);
	
	// Calculate ray direction
	ray->dir_x = cam_dir_x + plane_x * ray->cam_x;
	ray->dir_y = cam_dir_y + plane_y * ray->cam_x;
	
	// FIX: Use exact world coordinates as starting position, not tile coordinates
	ray->map_x = (int)(game->curr_x / TILE_SIZE);  // Floor to get current tile
	ray->map_y = (int)(game->curr_y / TILE_SIZE);  // Floor to get current tile
	
	// Debug: Print ray initialization for middle column only to avoid spam
	if (x == MAX_WIDTH / 2) {
		// printf("DEBUG RAY[%d]: Player at exact world (%.2f, %.2f) -> starting tile (%d, %d)\n", 
		//	x, game->curr_x, game->curr_y, ray->map_x, ray->map_y);
		// printf("DEBUG RAY[%d]: View angle %.3f -> cam_dir(%.3f, %.3f), plane(%.3f, %.3f)\n",
		//	x, game->view_direction, cam_dir_x, cam_dir_y, plane_x, plane_y);
		// printf("DEBUG RAY[%d]: Ray direction (%.3f, %.3f)\n", x, ray->dir_x, ray->dir_y);
	}
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
	
	/* Convert elevation angle to pixel offset for sky/floor boundary */
	int elevation_offset = (int)(tan(game->view_elevation) * (MAX_HEIGHT / 2));
	midline = MAX_HEIGHT / 2 + elevation_offset;
	
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

// Function to get the appropriate texture based on hit tile type
t_image	*get_surface_texture(t_game *game, t_ray *ray, char hit_tile)
{
	int door_id;
	
	if (hit_tile == TILE_WALL)
		return get_wall_texture(game, ray->side, ray->dir_x, ray->dir_y);
	else if (hit_tile == HORIZ_DOOR)
	{
		door_id = get_door_id(game, ray->map_x, ray->map_y);
		if (door_id >= 0)
		{
			// H door: door texture on East/West faces, wall texture on North/South faces
			if (ray->side == 0)  // Vertical face (East/West)
				return get_door_texture(game, door_id, game->doors[door_id].animation_frame);
			else  // Horizontal face (North/South)
				return get_wall_texture(game, ray->side, ray->dir_x, ray->dir_y);
		}
		// Fallback to wall texture if door not found
		return get_wall_texture(game, ray->side, ray->dir_x, ray->dir_y);
	}
	else if (hit_tile == VERTI_DOOR)
	{
		door_id = get_door_id(game, ray->map_x, ray->map_y);
		if (door_id >= 0)
		{
			// V door: door texture on North/South faces, wall texture on East/West faces
			if (ray->side == 1)  // Horizontal face (North/South)
				return get_door_texture(game, door_id, game->doors[door_id].animation_frame);
			else  // Vertical face (East/West)
				return get_wall_texture(game, ray->side, ray->dir_x, ray->dir_y);
		}
		// Fallback to wall texture if door not found
		return get_wall_texture(game, ray->side, ray->dir_x, ray->dir_y);
	}
	
	return game->textures.north_wall; // fallback
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
	// FIX: Use exact world coordinates divided by tile size to get fractional position within tile
	double curr_tile_x = game->curr_x / TILE_SIZE;  // Exact position in tile coordinates
	double curr_tile_y = game->curr_y / TILE_SIZE;  // Exact position in tile coordinates
	
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (curr_tile_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - curr_tile_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (curr_tile_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - curr_tile_y) * ray->delta_y;
	}
}
