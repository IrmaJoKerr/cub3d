/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 07:33:18 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 18:54:07 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
void	debug_print_map(t_game *game);
void debug_print_line(const char *line, int line_number);

/**
 * Debug function to print the entire 2D map array
 */
void	debug_print_map(t_game *game)
{
	int	y;

	if (!game || !game->map.map)
	{
		fprintf(stderr, "[DEBUG] Map is NULL or not allocated\n");
		return ;
	}

	fprintf(stderr, "\n=== DEBUG: MAP CONTENTS ===\n");
	fprintf(stderr, "Map dimensions: %dx%d\n", game->map.max_cols, game->map.max_rows);
	fprintf(stderr, "Player position: (%.2f, %.2f)\n", game->map.player_x, game->map.player_y);
	fprintf(stderr, "Player count: %d\n", game->map.herocount);
	fprintf(stderr, "Start direction: %d\n", game->map.start_direction);
	fprintf(stderr, "\nMap array contents:\n");
	y = 0;
	while (y < game->map.max_rows)
	{
		if (game->map.map[y])
			fprintf(stderr, "Row %2d: [%s]\n", y, game->map.map[y]);
		else
			fprintf(stderr, "Row %2d: [NULL]\n", y);
		y++;
	}
	fprintf(stderr, "=== END DEBUG MAP ===\n\n");
}

void debug_print_line(const char *line, int line_number)
{
	if (line)
		fprintf(stderr, "[DEBUG] Line %d: %s\n", line_number, line);
	else
		fprintf(stderr, "[DEBUG] Line %d: [NULL]\n", line_number);
}

