/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:50:35 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/03 10:42:27 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"
/*
static void	map_dimensions(t_data *data)
{
	int		x;
	int		y;
	int		max_x;
	char	**map;
	
	y = 0;
	max_x = 0;
	map = data->map_data.dungeon;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
			x++;
		if (x > max_x)
			max_x = x;
		y++;
	}
	printf("%d\n%d", max_x, y);
}
*/

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data*)param;
	if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
		rotate(data, -1);
	if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
		rotate(data, 1);
	if (mlx_is_key_down(data->window, MLX_KEY_W))
		move_forward(data);
	if (mlx_is_key_down(data->window, MLX_KEY_S))
		move_backward(data);
	if (mlx_is_key_down(data->window, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(data->window, MLX_KEY_D))
		move_right(data);
	mouse_look(data);
	fill_background(data);
	cast_rays(data);
	draw_map(data);
}

int	main(int argc, char **argv)
{
	t_data	gamedata;

	ft_bzero(&gamedata, sizeof(t_data));
	if (parse_input(&gamedata.map_data, argc, argv))
		return (EXIT_FAILURE);
	//map_dimensions(&gamedata);
	init_player_start(&gamedata);
	open_window(&gamedata);
	if (!gamedata.window)
		return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);
	gamedata.img = mlx_new_image(gamedata.window, WIDTH, HEIGHT);
	gamedata.minimap = mlx_new_image(gamedata.window, 400, 400);
	gamedata.minimap->enabled = false;
	mlx_image_to_window(gamedata.window, gamedata.img, 0, 0);
	mlx_image_to_window(gamedata.window, gamedata.minimap, 50, gamedata.window->height - 200);
	mlx_key_hook(gamedata.window, &key_hook, &gamedata);
	mlx_resize_hook(gamedata.window, &resize_hook, &gamedata);
	mlx_loop_hook(gamedata.window, &game_loop, &gamedata);
	printf("Window opened! Press ESC to close.\n");
	mlx_loop(gamedata.window);
	mlx_terminate(gamedata.window);
	wipe_map(&gamedata.map_data);
	return (EXIT_SUCCESS);
}
