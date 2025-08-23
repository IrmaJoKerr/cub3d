/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:29:37 by bleow             #+#    #+#             */
/*   Updated: 2025/08/23 07:44:34 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*
Function prototypes
*/
// char	*get_map_path(const char *map_file);
// int		check_valid_file_path(const char *path);
// void	load_texture(t_game *game, t_image *tex, char *path);
int		count_door_textures(void);
void	load_all_door_textures(t_game *game);
void	cleanup_framebuffer(t_game *game);
void	init_game(t_game *game, const char *map_file);

/*
Build the full path to the map file.
If the map_file contains a '/', use it as-is.
Otherwise, prepend "maps/" to look in the maps subfolder.
*/
/*
Old get_map_path logic commented out below for reference.
// char	*get_map_path(const char *map_file)
// {
//     char	*full_path;
//     full_path = NULL;
//     if (ft_strncmp(map_file, "maps/", 5) == 0)
//         full_path = ft_strdup(map_file);
//     else
//         full_path = ft_strjoin("maps/", map_file);
int	check_builtin_textures(void);
//     {
//         ft_fprintf(2, "Error: \n");
//         ft_fprintf(2, "Failed to allocate memory for map path.\n");
//         return (NULL);
//     }
//     if (!check_valid_file_path(full_path))
//     {
//         free(full_path);
//         return (NULL);
//     }
//     return (full_path);
// }
*/

int	check_builtin_textures(t_game *game)
{
	int		i;
	char	path[256];
	char	*num;

	   if (!check_valid_file_path(SPACE_TEXTURE))
		   return (0);
	   i = 0;
	   while (i <= 7)
	   {
		   ft_strcpy(path, DOORS_TEXTURE);
		   ft_strcat(path, "door_");
		   num = ft_itoa(i);
		   ft_strcat(path, num);
		   free(num);
		   ft_strcat(path, ".xpm");
		   if (!check_valid_file_path(path))
			   return (0);
		   if (!load_door_texture(game, path, i))
			   return (0);
		   i++;
	   }
	   return (1);
}

// /*
// Unified map path resolution supporting valid/invalid subfolders.
// If input starts with maps/valid/ or maps/invalid/, use as-is if exists.
// Otherwise, try maps/invalid/ then maps/valid/. Returns first found or error.
// */
// char	*get_map_path(const char *input)
// {
// 	char	*test_path;

// 	if (ft_strncmp(input, "maps/valid/", 11) == 0
// 		|| ft_strncmp(input, "maps/invalid/", 13) == 0)
// 	{
// 		if (check_valid_file_path(input))
// 			return (ft_strdup(input));
// 	}
// 	else
// 	{
// 		test_path = ft_strjoin("maps/invalid/", input);
// 		if (check_valid_file_path(test_path))
// 			return (test_path);
// 		free(test_path);
// 		test_path = ft_strjoin("maps/valid/", input);
// 		if (check_valid_file_path(test_path))
// 			return (test_path);
// 		free(test_path);
// 	}
// 	ft_fprintf(2, "Error: Map file not found: %s\n", input);
// 	return (NULL);
// }

// int	check_valid_file_path(const char *path)
// {
// 	int		fd;

// 	if (!path || ft_strlen(path) == 0)
// 		return (0);
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	close(fd);
// 	return (1);
// }

// void	load_texture(t_game *game, t_image *tex, char *path)
// {
// 	int	width;
// 	int	height;

// 	tex->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
// 	if (!tex->img_ptr)
// 	{
// 		ft_fprintf(2, "Texture load failed: %s\n", path);
// 		exit(1);
// 	}
// 	if (width != TEX_WIDTH || height != TEX_HEIGHT)
// 	{
// 		ft_fprintf(2, "Invalid texture size (%dx%d): %s\n", width, height,
// 			path);
// 		exit(1);
// 	}
// 	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
// 			&tex->endian);
// 	tex->transparent_color = 0xFF000000;
// }

// int	count_door_textures(void)
// {
// 	int		count;
// 	char	path[256];

// 	count = 0;
// 	while (count < MAX_DOOR_FRAMES)
// 	{
// 		sprintf(path, "textures/doors/door_%d.xpm", count);
// 		if (!check_valid_file_path(path))
// 			break ;
// 		count++;
// 	}
// 	return (count);
// }

// void	load_all_door_textures(t_game *game)
// {
// 	int		i;
// 	char	path[256];
// 	int		door_count;

// 	door_count = count_door_textures();
// 	if (door_count == 0)
// 	{
// 		ft_fprintf(2, "Error: No door textures found in textures/doors/\n");
// 		exit(1);
// 	}
// 	ft_fprintf(1, "Loading %d door textures...\n", door_count);

// 	i = 0;
// 	while (i < door_count)
// 	{
// 		snprintf(path, sizeof(path), "textures/doors/door_%d.xpm", i);
// 		game->textures.door_frames[i] = malloc(sizeof(t_image));
// 		if (!game->textures.door_frames[i])
// 		{
// 			ft_fprintf(2, "Error: Failed to allocate door frame %d\n", i);
// 			exit(1);
// 		}
// 		load_texture(game, game->textures.door_frames[i], path);
// 		usleep(2000); // Small delay between door texture loads
// 		i++;
// 	}
// 	game->textures.door_frame_count = door_count;
// 	ft_fprintf(1, "✅ Loaded %d door animation frames\n", door_count);
// }

// DEPRECATION CANDIDATE: cleanup_framebuffer is no longer used. Use cleanup routines instead.
// void	cleanup_framebuffer(t_game *game)
// {
// 	mlx_destroy_image(game->mlx_ptr, game->img.img_ptr);
// 	game->img.img_ptr = NULL;
// 	game->img.addr = NULL;
// }

int	main(int argc, char **argv)
{
	t_game	*game;
	char	*map_path;

	chk_args(argc, argv);
	map_path = get_map_path(argv[1]);
	if (!map_path)
		return (1);
	alloc_and_init_all(&game);
	init_game(game, map_path);
	free(map_path);
	setup_event_hooks(game);
	mlx_loop_hook(game->mlx_ptr, render_img, game);
	mlx_loop(game->mlx_ptr);
	cleanup(game);
	return (0);
}

// Deprecated implementations (replaced by cub3D_utils.c)
// char	*get_map_path(const char *input) { ... }
// int	check_valid_file_path(const char *path) { ... }
// void	load_texture(t_game *game, t_image *tex, char *path) { ... }
// int	count_door_textures(void) { ... }
// void	load_all_door_textures(t_game *game) { ... }
