/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:50:35 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/02 15:17:52 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

void	open_window(t_data *data)
{
	// 1. Initialize MLX (Width, Height, Title, Resizeable)
	data->window = mlx_init(WIDTH, HEIGHT, "Chaplin Moustache Hunting Club", true);
	/*
	if (!data->window)
		cleanup function
	*/
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data *data;
	
	data = (t_data*)param;
	mlx_resize_image(data->img, width, height);
}

// Hook function to handle key input
void	key_hook(mlx_key_data_t pressed_key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (pressed_key.action == MLX_PRESS || pressed_key.action == MLX_REPEAT)
	{
		if (pressed_key.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->window);
	}
}

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
	fill_background(data);
	//draw_map(data);
	cast_rays(data);
}

int	main(int argc, char **argv)
{
	t_data	gamedata;

	ft_bzero(&gamedata, sizeof(t_data));
	if (parse_input(&gamedata.map_data, argc, argv))
		return (EXIT_FAILURE);
	init_player_start(&gamedata);
	open_window(&gamedata);
	if (!gamedata.window)
	{
		// MLX42 has a built-in error string function
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	gamedata.img = mlx_new_image(gamedata.window, WIDTH, HEIGHT);
	mlx_image_to_window(gamedata.window, gamedata.img, 0, 0);
	mlx_key_hook(gamedata.window, &key_hook, &gamedata);
	mlx_resize_hook(gamedata.window, &resize_hook, &gamedata);
	mlx_loop_hook(gamedata.window, &game_loop, &gamedata);
	printf("Window opened! Press ESC to close.\n");
	mlx_loop(gamedata.window);

	mlx_terminate(gamedata.window);
	wipe_map(&gamedata.map_data);
	return (EXIT_SUCCESS);
}
