/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:34:42 by bleow             #+#    #+#             */
/*   Updated: 2025/07/05 12:39:06 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		close_window(t_game *game);
void	cleanup_early(t_game *game);
void	cleanup_later(t_game *game);
void	cleanup(t_game *game);

/*
Cleanup function to free memory and exit the program.
*/
void	cleanup(t_game *game)
{
	usleep(1000000);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
}

/*
Exits the program early if there is an error.
*/
int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free(game->mlx_ptr);
	free(game);
	exit(EXIT_SUCCESS);
}

/*
Cleanup if error before mlx initialization.
*/
void	cleanup_early(t_game *game)
{
	free(game);
	exit(EXIT_FAILURE);
}

/*
Cleanup if error after mlx initialization.
*/
void	cleanup_later(t_game *game)
{
	free(game->mlx_ptr);
	free(game);
	exit(EXIT_FAILURE);
}
