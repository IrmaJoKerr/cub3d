/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:03:44 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 17:46:35 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		parse_floor_color(char *line, t_game *game);
int		parse_ceiling_color(char *line, t_game *game);
char	*extract_color_values(const char *line, const char *identifier);
int		validate_color_values(const char *values, int color[3]);
int		chk_color_range(int *converted_colors, int color[3]);

/*
Parse and set the floor color from a config line (F).
*/
int	parse_floor_color(char *line, t_game *game)
{
	char	*values;
	int		color[3];
	int		result;

	fprintf(stderr, "[DEBUG] parse_floor_color: Entering with line='%s'\n", line);
	values = extract_color_values(line, "F");
	fprintf(stderr, "[DEBUG] parse_floor_color: Extracted values='%s'\n", values ? values : "NULL");
	result = validate_color_values(values, color);
	fprintf(stderr, "[DEBUG] parse_floor_color: Validation result=%d, color={%d,%d,%d}\n", result, color[0], color[1], color[2]);
	if (result == 0)
	{
		game->map.floor_color[0] = color[0];
		game->map.floor_color[1] = color[1];
		game->map.floor_color[2] = color[2];
		fprintf(stderr, "[DEBUG] parse_floor_color: Assigned floor_color={%d,%d,%d}\n", color[0], color[1], color[2]);
	}
	if (values)
		free(values);
	fprintf(stderr, "[DEBUG] parse_floor_color: Exiting with result=%d\n", result);
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

	fprintf(stderr, "[DEBUG] parse_ceiling_color: Entering with line='%s'\n", line);
	values = extract_color_values(line, "C");
	fprintf(stderr, "[DEBUG] parse_ceiling_color: Extracted values='%s'\n", values ? values : "NULL");
	result = validate_color_values(values, color);
	fprintf(stderr, "[DEBUG] parse_ceiling_color: Validation result=%d, color={%d,%d,%d}\n", result, color[0], color[1], color[2]);
	if (result == 0)
	{
		game->map.sky_color[0] = color[0];
		game->map.sky_color[1] = color[1];
		game->map.sky_color[2] = color[2];
		fprintf(stderr, "[DEBUG] parse_ceiling_color: Assigned sky_color={%d,%d,%d}\n", color[0], color[1], color[2]);
	}
	if (values)
		free(values);
	fprintf(stderr, "[DEBUG] parse_ceiling_color: Exiting with result=%d\n", result);
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
	{
		fprintf(stderr, "[DEBUG] validate_color_values: NULL values string\n");
		return (-1);
	}
	numbers = ft_split(values, ',');
	if (!numbers)
	{
		fprintf(stderr, "[DEBUG] validate_color_values: ft_split failed\n");
		return (-1);
	}
	num_count = ft_arrlen(numbers);
	fprintf(stderr, "[DEBUG] validate_color_values: num_count=%d\n", num_count);
	if (num_count != 3)
	{
		fprintf(stderr, "[DEBUG] validate_color_values: invalid number of color components\n");
		ft_free_2d(numbers, num_count);
		return (-1);
	}
	converted_colors = ft_atoiarr_errcln(numbers, num_count);
	if (!converted_colors)
	{
		fprintf(stderr, "[DEBUG] validate_color_values: ft_atoiarr_errcln failed\n");
		return (-1);
	}
	if (chk_color_range(converted_colors, color) != 0)
	{
		fprintf(stderr, "[DEBUG] validate_color_values: color out of range\n");
		free(converted_colors);
		return (-1);
	}
	fprintf(stderr, "[DEBUG] validate_color_values: parsed color={%d,%d,%d}\n", color[0], color[1], color[2]);
	free(converted_colors);
	return (0);
}
