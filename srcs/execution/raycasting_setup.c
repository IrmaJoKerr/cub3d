#include "../includes/raycasting.h"
#include "../includes/cub3D.h"
#include <sys/time.h>

// Get current time in milliseconds
long get_current_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	render_raycast(t_game *game)
{
	int x;
	static int frame_count = 0;

	// Only render if something actually changed
	if (!game->needs_render)
		return;
		
	// Check frame rate limit AFTER deciding to render
	long current_time = get_current_time_ms();
	if (current_time - game->last_frame_time < 16) // 60 FPS limit
		return;

	x = 0;
	// Create image buffer only once, reuse for all subsequent frames
	if (!game->img.img_ptr)
	{
		game->img.img_ptr = mlx_new_image(game->mlx_ptr, MAX_WIDTH, MAX_HEIGHT);
		game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
										   &game->img.line_len, &game->img.endian);
	}
									   
	// Debug: Print render info every 60 frames to avoid spam
	if (frame_count % 60 == 0) {
		// printf("DEBUG RENDER[frame %d]: Rendering from player pos (%.2f, %.2f), view_angle %.3f\n", 
		//	frame_count, game->curr_x, game->curr_y, game->view_direction);
	}
	frame_count++;
	
	// Update door animations
	update_door_animations(game);
	
	// Render complete frame to buffer BEFORE displaying
	fill_sky_and_floor(game);
	while (x < MAX_WIDTH)
		render_column(game, x++);
		
	// Only display after complete frame is rendered
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
	
	// Mark frame as rendered
	game->needs_render = false;
	game->last_frame_time = current_time;
}
int	render_img(t_game *game)
{
	render_map(game);
	render_raycast(game);
	draw_crosshair(game);
	return (0);
}
