/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:37:30 by bleow             #+#    #+#             */
/*   Updated: 2025/08/17 10:21:20 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	chk_args(int argc, char **argv)
{
	int	pos;

	pos = 0;
	if (argc != 2)
	{
		ft_fprintf(2, "Error\n");
		ft_fprintf(2, "Wrong argument syntax.\n");
		ft_fprintf(2, "Correct Syntax Examples:\n");
		ft_fprintf(2, "./cub3D test.cub");
		ft_fprintf(2, "Or\n");
		ft_fprintf(2, "./cub3D maps/test.cub");
		exit(1);
	}
	while (argv[1][pos] != '\0')
		pos++;
	pos -= 4;
	if (ft_strncmp(&argv[1][pos], ".cub", 4) != 0)
	{
		ft_fprintf(2, "Error\n");
		ft_fprintf(2, "Map file must end with .cub extension.\n");
		exit(1);
	}
	return ;
}

/**
 * Validate XMP extension using "end-4" logic
 * Go to end of string, back up 4 places, and match .xpm
 */
int	validate_xmp_extension(const char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	// Go to end, back up 4 places, match ".xpm"
	return (ft_strcmp(&path[len - 4], ".xpm") == 0);
}

/**
 * Enhanced texture path validation with XMP extension check
 */
int	check_valid_texture_path(const char *path)
{
	int		fd;

	if (!path || ft_strlen(path) == 0)
	{
		ft_fprintf(2, "Error: Empty texture path\n");
		return (0);
	}
	if (!validate_xmp_extension(path))
	{
		ft_fprintf(2, "Error: Texture file must have .xpm extension: %s\n", path);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error: Cannot access texture file: %s\n", path);
		return (0);
	}
	close(fd);
	return (1);
}
