#include "../includes/raycasting.h"

void	render_raycast(t_game *game)
{
	int x;

	x = 0;
	if (game->img.img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
	game->img.img_ptr = mlx_new_image(game->mlx_ptr, MAX_WIDTH, MAX_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
									   &game->img.line_len, &game->img.endian);
	fill_sky_and_floor(game);
	while (x < MAX_WIDTH)
		render_column(game, x++);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
}

void draw_crosshair(t_game *game)
{
	int cx = MAX_WIDTH / 2;
	int cy = MAX_HEIGHT / 2;
	int size = 10;

	// Horizontal line
	for (int dx = -size; dx <= size; dx++)
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, cx + dx, cy, 0xFFFFFF);

	// Vertical line
	for (int dy = -size; dy <= size; dy++)
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, cx, cy + dy, 0xFFFFFF);
}

int	render_img(t_game *game)
{
	render_raycast(game);
	draw_crosshair(game);
	return (0);
}