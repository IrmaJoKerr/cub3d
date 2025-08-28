/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:03:44 by bleow             #+#    #+#             */
/*   Updated: 2025/08/25 19:14:58 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		parse_floor_color(char *line, t_game *game);
int		parse_ceiling_color(char *line, t_game *game);
char	*extract_color_values(const char *line, const char *identifier);
int		chk_color_range(int *converted_colors, int color[3]);
int		validate_color_values(const char *values, int color[3]);

/*
Parse and set the floor color from a config line (F).
*/
int	parse_floor_color(char *line, t_game *game)
{
	char	*values;
	int		color[3];
	int		result;

	values = extract_color_values(line, "F");
	result = validate_color_values(values, color);
	if (result == 0)
	{
		game->map.floor_color[0] = color[0];
		game->map.floor_color[1] = color[1];
		game->map.floor_color[2] = color[2];
	}
	if (values)
		ft_safefree((void **)&values);
	return (result);
}

/*
Parse and set the ceiling color from a config line (C).
*/
int	parse_ceiling_color(char *line, t_game *game)
{
	char	*values;
	int		color[3];
	int		result;

	values = extract_color_values(line, "C");
	result = validate_color_values(values, color);
	if (result == 0)
	{
		game->map.sky_color[0] = color[0];
		game->map.sky_color[1] = color[1];
		game->map.sky_color[2] = color[2];
	}
	if (values)
		ft_safefree((void **)&values);
	return (result);
}

/*
Extract the comma-separated RGB values from a config line.
*/
char	*extract_color_values(const char *line, const char *identifier)
{
	int		i;
	int		start;
	char	*values;

	i = ft_strlen(identifier);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	values = malloc(sizeof(char) * (i - start + 1));
	if (!values)
		return (NULL);
	ft_strncpy(values, line + start, i - start);
	values[i - start] = '\0';
	return (values);
}

/*
Validate RGB values are in [0,255] and copy to output array.
*/
int	chk_color_range(int *converted_colors, int color[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (converted_colors[i] < 0 || converted_colors[i] > 255)
			return (-1);
		color[i] = converted_colors[i];
		i++;
	}
	return (0);
}

/*
Convert and validate RGB values from string, using ft_atoiarr_errcln
for error handling.
*/
int	validate_color_values(const char *values, int color[3])
{
	char	**numbers;
	int		*converted_colors;
	int		num_count;

	if (!values)
		return (-1);
	numbers = ft_split(values, ',');
	if (!numbers)
		return (-1);
	num_count = ft_arrlen(numbers);
	if (num_count != 3)
	{
		ft_free_2d(numbers, num_count);
		return (-1);
	}
	converted_colors = ft_atoiarr_errcln(numbers, num_count);
	if (!converted_colors)
		return (-1);
	if (chk_color_range(converted_colors, color) != 0)
	{
		ft_safefree((void **)&converted_colors);
		return (-1);
	}
	ft_safefree((void **)&converted_colors);
	return (0);
}
