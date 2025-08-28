/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:37:30 by bleow             #+#    #+#             */
/*   Updated: 2025/08/25 19:55:27 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/*
Function prototypes
*/
void	chk_args(int argc, char **argv);
char	*get_map_path(char *input);
int		validate_xmp_extension(const char *path);
char	*build_door_path(int i);

/*
Validates command-line arguments and ensures the map file has a `.cub` extension.
Exits on failure.
*/
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

/*
Resolve the correct map path based on input and available files
*/
char	*get_map_path(char *input)
{
	char	*test_path;

	test_path = NULL;
	if (ft_strncmp(input, "maps/valid/", 11) == 0
		|| ft_strncmp(input, "maps/invalid/", 13) == 0)
	{
		if (check_valid_file_path(input))
			return (ft_strdup(input));
	}
	else
	{
		test_path = ft_strjoin("maps/invalid/", input);
		if (check_valid_file_path(test_path))
			return (test_path);
		else if (test_path)
			ft_safefree((void **)&test_path);
		test_path = ft_strjoin("maps/valid/", input);
		if (check_valid_file_path(test_path))
			return (test_path);
		else if (test_path)
			ft_safefree((void **)&test_path);
	}
	return (NULL);
}

/*
Validate XMP extension. Go to end of string, back up 4 places, and match .xpm
*/
int	validate_xmp_extension(const char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strcmp(&path[len - 4], ".xpm") == 0);
}

/*
Generate the file path for a door texture.
*/
char	*build_door_path(int i)
{
	char	path[256];
	char	*num;

	ft_strcpy(path, DOORS_TEXTURE);
	ft_strcat(path, "door_");
	num = ft_itoa(i);
	ft_strcat(path, num);
	free(num);
	ft_strcat(path, ".xpm");
	return (ft_strdup(path));
}
