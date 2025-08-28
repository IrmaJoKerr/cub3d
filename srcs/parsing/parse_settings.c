/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:45:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/25 19:04:47 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		identify_settings_type(const char *line);
char	*extract_texture_path(const char *line, const char *identifier);

/*
Identifies the type of setting based on the given line.
Returns an integer representing the setting type, or 0 if unrecognized.
*/
int	identify_settings_type(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, "NO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line + i, "SO ", 3) == 0)
		return (2);
	else if (ft_strncmp(line + i, "WE ", 3) == 0)
		return (3);
	else if (ft_strncmp(line + i, "EA ", 3) == 0)
		return (4);
	else if (ft_strncmp(line + i, "F ", 2) == 0)
		return (5);
	else if (ft_strncmp(line + i, "C ", 2) == 0)
		return (6);
	else
		return (0);
}

/*
Extracts the texture path from a given line based on the identifier.
Returns the extracted path as a string, or NULL on failure.
*/
char	*extract_texture_path(const char *line, const char *identifier)
{
	int		i;
	int		start;
	int		len;
	char	*path;

	i = 0;
	path = NULL;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	i += ft_strlen(identifier);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	len = i - start;
	if (len == 0)
		return (NULL);
	path = ft_calloc(len + 1, sizeof(char));
	if (!path)
		return (NULL);
	ft_strncpy(path, line + start, len);
	path[len] = '\0';
	return (path);
}
