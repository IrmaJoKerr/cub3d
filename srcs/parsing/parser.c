/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 07:26:12 by bleow             #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/08/17 16:21:40 by bleow            ###   ########.fr       */
=======
/*   Updated: 2025/08/23 13:05:39 by bleow            ###   ########.fr       */
>>>>>>> Stashed changes
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

	fprintf(stderr, "[DEBUG] Entering parse_map for file: %s\n", file);
	ft_fprintf(2, "Starting two-pass parsing for file: %s\n", file);
	map_start_line = parse_configuration_section(file, game);
	fprintf(stderr, "[DEBUG] parse_configuration_section returned: %d\n", map_start_line);
	if (map_start_line < 0)
	{
		fprintf(stderr, "[DEBUG] Error: Failed to parse configuration section\n");
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Failed to parse configuration section\n");
		ft_fprintf(2, "Failed to parse and validate the map.\n");
		return (-1);
	}
<<<<<<< Updated upstream
	ft_fprintf(2, "Configuration parsed successfully.\nMap starts at line %d\n", map_start_line);
=======
	ft_fprintf(2, "Config parsed successfully.\nMap starts at line %d\n",
		map_start_line);
	fprintf(stderr, "[DEBUG] Calling parse_map_section at line %d\n", map_start_line);
>>>>>>> Stashed changes
	if (parse_map_section(file, game, map_start_line) < 0)
	{
		fprintf(stderr, "[DEBUG] Error: Failed to parse map section\n");
		ft_fprintf(2, "Error: \n");
		ft_fprintf(2, "Failed to parse map section\n");
		ft_fprintf(2, "Failed to parse and validate the map.\n");
		return (-1);
	}
	fprintf(stderr, "[DEBUG] Two-pass parsing completed successfully\n");
	ft_fprintf(2, "Two-pass parsing completed successfully\n");
	return (1);
}
