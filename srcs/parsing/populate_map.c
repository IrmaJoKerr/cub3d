/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 03:09:02 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 18:22:24 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		populate_map_array(const char *file, t_game *game);
// int	prepare_map_array(const char *file, t_game *game);
void	copy_line(char *dest, const char *src, int max_cols, int row);
int		skip_to_map(int fd, int map_start_line);
int		fill_map(int fd, t_game *game);
int		prepare_map_array(t_game *game);

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
// 		fprintf(stderr, "Error: Failed to allocate memory for map\n");
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
// 			fprintf(stderr, "Error: Failed to allocate memory for map line\n");
// 			free(line);
// 			close(fd);
// 			return (-1);
// 		}
// 		ft_memset(game->map.map[map_row], ' ', game->map.max_cols);
// 		game->map.map[map_row][game->map.max_cols] = '\0';
// 		int i = 0;
// 		int line_len = ft_strlen(line);
// 		fprintf(stderr, "Row %d: line_len=%d, max_cols=%d\n", map_row, line_len, game->map.max_cols);
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
// 			// fprintf(stderr, "Error: Last map line must contain only walls and spaces\n");
// 			// close(fd);
// 			// return (-1);
// 			// game->map.map_last_wall = false;    // OBSOLETE FIELD
// 		}
// 	}
// 	game->map.map[map_row] = NULL;
// 	close(fd);
// 	return (0);
// }

/*
Skips lines in the file until reaching the start of the map.
*/
int	skip_to_map(int fd, int map_start_line)
{
	int		line_num;
	char	*line;

	line_num = 0;
	while (line_num < map_start_line)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
		line_num++;
	}
	return (0);
}

/*
Copies a line into the map row.
*/
void	copy_line(char *dest, const char *src, int max_cols, int row)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = ft_strlen(src);
	while (i < line_len && i < max_cols)
	{
		dest[i] = src[i];
		i++;
	}
}


/*
Reads and copies map lines into the preallocated array.
*/
int	fill_map(int fd, t_game *game)
{
	int		map_row;
	char	*line;
	size_t	line_length;

	map_row = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_length = ft_strlen(line);
		if (line_length > 0 && line[line_length - 1] == '\n')
		{
			line[line_length - 1] = '\0';
		}
		ft_strlcpy(game->map.map[map_row], line, game->map.max_cols + 1);
		ft_safefree((void **)&line);
		map_row++;
		line = get_next_line(fd);
	}
	if (line)
		ft_safefree((void **)&line);
	return (0);
}

/*
Allocates and initializes the entire 2D map array up front.
Aborts and runs cleanup if max_rows or max_cols are invalid.
*/
int	prepare_map_array(t_game *game)
{
	int	i;

	// Free previously allocated memory for map if it exists
	if (game->map.map)
	{
		i = 0;
		while (i < game->map.max_rows)
		{
			if (game->map.map[i])
				free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}

	if (game->map.max_rows <= 0 || game->map.max_cols <= 0)
		return (-1);
	i = 0;
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.max_rows + 1));
	if (!game->map.map)
	{
		return (-1);
	}
	while (i < game->map.max_rows)
	{
		game->map.map[i] = (char *)malloc(game->map.max_cols + 1);
		if (!game->map.map[i])
		{
			while (--i >= 0) // Free previously allocated rows
				free(game->map.map[i]);
			free(game->map.map);
			game->map.map = NULL;
			return (-1);
		}
		ft_memset(game->map.map[i], ' ', game->map.max_cols);
		game->map.map[i][game->map.max_cols] = '\0';
		i++;
	}
	game->map.map[game->map.max_rows] = NULL;
	return (0);
}

/*
Populate 2D map array from file. Returns 0 on success, -1 on error.
*/
int	populate_map_array(const char *file, t_game *game)
{
	int		fd;
	int		map_row;

	fd = open(file, O_RDONLY);
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
	map_row = fill_map(fd, game);
	if (map_row < 0)
	{
		cleanup_map_array(game);
		close(fd);
		return (-1);
	}
	game->map.map[map_row] = NULL;
	close(fd);
	return (0);
}

/**
 * Wrapper function for get_next_line that duplicates the returned line
 * and immediately frees the original.
 *
 * @param fd File descriptor to read from.
 * @return A duplicated string of the line read, or NULL if EOF or error.
 */
char *get_next_line_safe(int fd)
{
	char *line;
	char *line_dup;

	line = get_next_line(fd);
	if (!line)
		return NULL;

	line_dup = ft_strdup(line);
	ft_safefree((void **)&line);

	return line_dup;
}
