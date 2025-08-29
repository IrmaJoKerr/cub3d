/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 03:09:02 by bleow             #+#    #+#             */
/*   Updated: 2025/08/29 17:33:25 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		populate_map_array(const char *file, t_game *game);
int		prepare_map_array(t_game *game);
int		skip_to_map(int fd, int map_start_line);
int		fill_map(int fd, t_game *game);
void	verify_print_map(t_game *game);

/*
Populate 2D map array from file.
*/
int	populate_map_array(const char *file, t_game *game)
{
	int	fd;

	fd = open_map_file(file);
	if (fd < 0)
		return (-1);
	if (prepare_map_array(game) < 0)
		return (-1);
	if (skip_to_map(fd, game->map.map_start_line) < 0)
	{
		cleanup_map_array(game);
		close(fd);
		return (-1);
	}
	if (fill_map(fd, game) < 0)
	{
		cleanup_map_array(game);
		close(fd);
		return (-1);
	}
	close(fd);
	verify_print_map(game);
	return (0);
}

/*
Allocates and initializes the entire 2D map array up front.
Aborts and runs cleanup if max_rows or max_cols are invalid.
*/
int	prepare_map_array(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.max_rows <= 0 || game->map.max_cols <= 0)
		return (-1);
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.max_rows + 1));
	if (!game->map.map)
		return (-1);
	while (i < (game->map.max_rows))
	{
		game->map.map[i] = (char *)malloc(game->map.max_cols + 1);
		if (!game->map.map[i])
		{
			ft_fprintf(2, "Error: Failed to alloc for map row %d.\n", i);
			cleanup_map_array(game);
			return (-1);
		}
		ft_memset(game->map.map[i], ' ', game->map.max_cols);
		game->map.map[i][game->map.max_cols] = '\0';
		ft_fprintf(2, "Allocated row %d\n", i);
		i++;
	}
	ft_fprintf(2, "Map alloc success. Total rows: %d\n", game->map.max_rows);
	return (0);
}

/*
Skips lines in the file until reaching the start of the map.
*/
int	skip_to_map(int fd, int map_start_line)
{
	int		line_num;
	char	*line;

	line_num = 1;
	line = get_next_line(fd);
	while (line_num < (map_start_line - 1))
	{
		if (line)
			ft_safefree((void **)&line);
		line_num++;
		line = get_next_line(fd);
	}
	if (line)
		ft_safefree((void **)&line);
	return (0);
}

/*
Reads and copies map lines into the preallocated array.
*/
int	fill_map(int fd, t_game *game)
{
	int		map_row;
	char	*line;
	size_t	line_length;
	int		i;

	map_row = 0;
	i = 0;
	line = get_next_line(fd);
	while (i < (game->map.max_rows) && line != NULL)
	{
		line_length = ft_strlen(line);
		if (line_length > 0 && line[line_length - 1] == '\n')
			line[line_length - 1] = '\0';
		ft_strlcpy(game->map.map[map_row], line, game->map.max_cols + 1);
		ft_safefree((void **)&line);
		map_row++;
		i++;
		line = get_next_line(fd);
	}
	game->map.map[map_row] = NULL;
	if (line)
		ft_safefree((void **)&line);
	return (0);
}

/*
Validation function to print the entire 2D map array
*/
void	verify_print_map(t_game *game)
{
	int	y;

	if (!game || !game->map.map)
	{
		ft_fprintf(2, "Error: Map is NULL or not allocated\n");
		return ;
	}
	ft_fprintf(2, "\n=== MAP CONTENTS ===\n");
	ft_fprintf(2, "Map dimensions: %dx%d\n", game->map.max_cols,
		game->map.max_rows);
	ft_fprintf(2, "Player count: %d\n", game->map.herocount);
	ft_fprintf(2, "\nMap array contents:\n");
	y = 0;
	while (y < (game->map.max_rows) && game->map.map[y])
	{
		if (game->map.map[y])
			ft_fprintf(2, "Row %2d: [%s]\n", y, game->map.map[y]);
		else
			ft_fprintf(2, "Row %2d: [NULL]\n", y);
		y++;
	}
	ft_fprintf(2, "=============\n\n");
}
