/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjun-kea <wjun-kea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:37:30 by bleow             #+#    #+#             */
/*   Updated: 2025/07/11 22:22:20 by wjun-kea         ###   ########.fr       */
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
