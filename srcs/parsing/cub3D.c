/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleow <bleow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:29:37 by bleow             #+#    #+#             */
/*   Updated: 2025/08/23 08:16:24 by bleow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Function prototypes
*/
int	check_builtin_textures(t_game *game);
int	main(int argc, char **argv);


/*
Check and load builtin space and door textures.
Returns 1 on success, 0 on failure. 
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
