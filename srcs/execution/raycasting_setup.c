#include "../includes/raycasting.h"

void	render_raycast(t_game *game)
{
	int x;

	x = 0;
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

void update_doors(t_game *game)
{
    for (int i = 0; i < game->doorcount; i++)
    {
        t_door *door = &game->doors[i];

        double dx = door->x - game->curr_x;
        double dy = door->y - game->curr_y;
        double dist_sq = dx * dx + dy * dy;
        bool near_enough = dist_sq < 7;
        if (door->state == DOOR_CLOSED && near_enough)
            door->state = DOOR_OPENING;
        else if (door->state == DOOR_OPEN && !near_enough)
            door->state = DOOR_CLOSING;
        if (door->state == DOOR_OPENING)
        {
            door->openness += DOOR_ANIM_SPEED;
            if (door->openness >= 1.0)
            {
                door->openness = 1.0;
                door->state = DOOR_OPEN;
            }
        }
        else if (door->state == DOOR_CLOSING)
        {
            door->openness -= DOOR_ANIM_SPEED;
            if (door->openness <= 0.0)
            {
                door->openness = 0.0;
                door->state = DOOR_CLOSED;
            }
        }
        door->animation_frame = (int)(door->openness * (game->textures.door_frame_count - 1));
    }
}

int	render_img(t_game *game)
{
	render_raycast(game);
	update_doors(game);
	draw_crosshair(game);
	return (0);
}
