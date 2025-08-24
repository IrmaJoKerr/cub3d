/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:45:00 by bleow             #+#    #+#             */
/*   Updated: 2025/08/24 17:46:35 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
int		identify_settings_type(const char *line);
char	*extract_texture_path(const char *line, const char *identifier);
int		parse_color_settings(char *line, t_game *game, char settings);

int identify_settings_type(const char *line)
{
    int i;

    fprintf(stderr, "[identify_settings_type] Input line: '%s'\n", line);
    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (ft_strncmp(line + i, "NO ", 3) == 0) {
        fprintf(stderr, "[identify_settings_type] Detected NO\n");
        return (1);
    }
    if (ft_strncmp(line + i, "SO ", 3) == 0) {
        fprintf(stderr, "[identify_settings_type] Detected SO\n");
        return (2);
    }
    if (ft_strncmp(line + i, "WE ", 3) == 0) {
        fprintf(stderr, "[identify_settings_type] Detected WE\n");
        return (3);
    }
    if (ft_strncmp(line + i, "EA ", 3) == 0) {
        fprintf(stderr, "[identify_settings_type] Detected EA\n");
        return (4);
    }
    if (ft_strncmp(line + i, "F ", 2) == 0) {
        fprintf(stderr, "[identify_settings_type] Detected F\n");
        return (5);
    }
    if (ft_strncmp(line + i, "C ", 2) == 0) {
        fprintf(stderr, "[identify_settings_type] Detected C\n");
        return (6);
    }
    fprintf(stderr, "[identify_settings_type] No config detected\n");
    return (0);
}

char *extract_texture_path(const char *line, const char *identifier)
{
    int i;
    int start;
    int len;
    char *path;

    ft_fprintf(2, "[extract_texture_path] Input line: '%s', identifier: '%s'\n", line, identifier);
    i = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    i += ft_strlen(identifier);
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    start = i;
    while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
        i++;
    len = i - start;
    ft_fprintf(2, "[extract_texture_path] Extracted start=%d, len=%d\n", start, len);
    if (len == 0) {
        ft_fprintf(2, "[extract_texture_path] No path found\n");
        return (NULL);
    }
    path = malloc(sizeof(char) * (len + 1));
    if (!path) {
        ft_fprintf(2, "[extract_texture_path] Malloc failed\n");
        return (NULL);
    }
    ft_strncpy(path, line + start, len);
    path[len] = '\0';
    ft_fprintf(2, "[extract_texture_path] Extracted path: '%s'\n", path);
    return (path);
}

int	parse_color_settings(char *line, t_game *game, char settings)
{
	if (settings == 'F')
		return (parse_floor_color(line, game));
	else if (settings == 'C')
		return (parse_ceiling_color(line, game));
	else
		return (-1);
}
