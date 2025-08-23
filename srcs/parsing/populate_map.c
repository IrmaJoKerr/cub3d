/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 03:09:02 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 03:26:55 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
// int		populate_map_array(const char *file, t_game *game, int map_start_line);
int		populate_map_array(const char *file, t_game *game);
int		prepare_map_array(const char *file, t_game *game);

/*
Allocate and populate 2D map array
*/
// int	populate_map_array(const char *file, t_game *game, int map_start_line)
// {
// 	int		fd;
// 	char	*line;
// 	int		line_num;
// 	int		map_row;
// 	int		len;
// 	char	*last_line;

// 	game->map.map = (char **)malloc(sizeof(char *) * (game->map.max_rows + 1));
// 	if (!game->map.map)
// 	{
// 		ft_fprintf(2, "Error: Failed to allocate memory for map\n");
// 		return (-1);
// 	}
// 	ft_memset(game->map.map, 0, sizeof(char *) * (game->map.max_rows + 1));
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		free(game->map.map);
// 		game->map.map = NULL;
// 		return (-1);
// 	}
// 	line_num = 0;
// 	map_row = 0;
// 	while (line_num < map_start_line)
// 	{
// 		line = get_next_line(fd);
// 		if (line)
// 			free(line);
// 		line_num++;
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		len = ft_strlen(line);
// 		if (len > 0 && line[len - 1] == '\n')
// 			line[len - 1] = '\0';
// 		if (ft_strlen(line) == 0 || is_only_whitespace(line))
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		if (map_row >= game->map.max_rows)
// 		{
// 			free(line);
// 			break;
// 		}
// 		// Allocate memory for the row using max_cols for uniform sizing
// 		game->map.map[map_row] = (char *)malloc(game->map.max_cols + 1);
// 		if (!game->map.map[map_row])
// 		{
// 			ft_fprintf(2, "Error: Failed to allocate memory for map line\n");
// 			free(line);
// 			close(fd);
// 			return (-1);
// 		}
// 		ft_memset(game->map.map[map_row], ' ', game->map.max_cols);
// 		game->map.map[map_row][game->map.max_cols] = '\0';
// 		int i = 0;
// 		int line_len = ft_strlen(line);
// 		ft_fprintf(2, "Row %d: line_len=%d, max_cols=%d\n", map_row, line_len, game->map.max_cols);
// 		while (i < line_len && i < game->map.max_cols)
// 		{
// 			game->map.map[map_row][i] = line[i];
// 			i++;
// 		}
// 		free(line);
// 		map_row++;
// 	}
// 	if (map_row > 0)
// 	{
// 		last_line = game->map.map[map_row - 1];
// 		if (validate_border_line(last_line))
// 		{
// 			// game->map.map_last_wall = true;      // OBSOLETE FIELD
// 		}
// 		else
// 		{
// 			// Temporarily disable for debugging irregular maps
// 			// ft_fprintf(2, "Error: Last map line must contain only walls and spaces\n");
// 			// close(fd);
// 			// return (-1);
// 			// game->map.map_last_wall = false;    // OBSOLETE FIELD
// 		}
// 	}
// 	game->map.map[map_row] = NULL;
// 	close(fd);
// 	return (0);
// }

int	prepare_map_array(const char *file, t_game *game)
{
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.max_rows + 1));
	if (!game->map.map)
	{
		ft_fprintf(2, "Error: Failed to allocate memory for map\n");
		return (-1);
	}
	ft_memset(game->map.map, 0, sizeof(char *) * (game->map.max_rows + 1));
	return (0);
}

int	populate_map_array(const char *file, t_game *game)
{
	int		fd;

	if (prepare_map_array(file, game) < 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(game->map.map);
		game->map.map = NULL;
		return (-1);
	}
	line_num = 0;
	map_row = 0;
	while (line_num < map_start_line)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
		line_num++;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strlen(line) == 0 || is_only_whitespace(line))
		{
			free(line);
			continue ;
		}
		if (map_row >= game->map.max_rows)
		{
			free(line);
			break;
		}
		// Allocate memory for the row using max_cols for uniform sizing
		game->map.map[map_row] = (char *)malloc(game->map.max_cols + 1);
		if (!game->map.map[map_row])
		{
			ft_fprintf(2, "Error: Failed to allocate memory for map line\n");
			free(line);
			close(fd);
			return (-1);
		}
		ft_memset(game->map.map[map_row], ' ', game->map.max_cols);
		game->map.map[map_row][game->map.max_cols] = '\0';
		int i = 0;
		int line_len = ft_strlen(line);
		ft_fprintf(2, "Row %d: line_len=%d, max_cols=%d\n", map_row, line_len, game->map.max_cols);
		while (i < line_len && i < game->map.max_cols)
		{
			game->map.map[map_row][i] = line[i];
			i++;
		}
		free(line);
		map_row++;
	}
	if (map_row > 0)
	{
		last_line = game->map.map[map_row - 1];
		if (validate_border_line(last_line))
		{
			// game->map.map_last_wall = true;      // OBSOLETE FIELD
		}
		else
		{
			// Temporarily disable for debugging irregular maps
			// ft_fprintf(2, "Error: Last map line must contain only walls and spaces\n");
			// close(fd);
			// return (-1);
			// game->map.map_last_wall = false;    // OBSOLETE FIELD
		}
	}
	game->map.map[map_row] = NULL;
	close(fd);
	return (0);
}