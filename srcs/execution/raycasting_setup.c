#include "../includes/raycasting.h"

void	render_raycast(t_game *game)
{
	int x;

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
int	render_img(t_game *game)
{
	render_raycast(game);
	return (0);
}