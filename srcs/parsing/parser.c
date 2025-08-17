/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:26:12 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 10:40:02 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
Function prototypes
*/
int	parse_map(const char *file, t_game *game);

/*
Main parsing and validation function implementing proper two-pass architecture:
Pass 1: Parse configuration settings (textures, colors) until map starts
Pass 2: Calculate map dimensions, allocate memory, and populate map
*/
int	parse_map(const char *file, t_game *game)
{
	int	map_start_line;

	ft_fprintf(2, "Starting two-pass parsing for file: %s\n", file);
	map_start_line = parse_configuration_section(file, game);
	if (map_start_line < 0)
	{
		ft_fprintf(2, "Error: Failed to parse configuration section\n");
		return (-1);
	}
	ft_fprintf(2, "Configuration parsed successfully. Map starts at line %d\n", map_start_line);
	if (parse_map_section(file, game, map_start_line) < 0)
	{
		ft_fprintf(2, "Error: Failed to parse map section\n");
		return (-1);
	}
	ft_fprintf(2, "Two-pass parsing completed successfully\n");
	return (1);
}
