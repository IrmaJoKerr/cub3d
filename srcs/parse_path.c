/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:37:30 by bleow             #+#    #+#             */
/*   Updated: 2025/07/11 10:26:36 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	chk_args(int argc, char **argv)
{
	int	pos;

	pos = 0;
	if (argc != 2)
	{
		ft_printf("Error\n");
		ft_printf("Wrong argument syntax.\n");
		ft_printf("Correct Syntax Examples:\n");
		ft_printf("./cub3D test.cub");
		ft_printf("Or\n");
		ft_printf("./cub3D maps/test.cub");
		exit(1);
	}
	while (argv[1][pos] != '\0')
		pos++;
	pos -= 4;
	if (ft_strncmp(&argv[1][pos], ".cub", 4) != 0)
	{
		ft_printf("Error\n");
		ft_printf("Map file must end with .cub extension.\n");
		exit(1);
	}
	return ;
}
