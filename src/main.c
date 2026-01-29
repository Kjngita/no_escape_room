/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:50:35 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/29 21:03:59 by jjahkola         ###   ########.fr       */
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
	if (mlx_is_key_down(data->window, MLX_KEY_UP))
		move_forward(data);
	if (mlx_is_key_down(data->window, MLX_KEY_DOWN))
		move_backward(data);
	fill_background(data);
	//draw_compass(data);
	//draw_map(data);
	cast_rays(data);

}

int	main(int argc, char **argv)
{
	t_data	gamedata;

	ft_bzero(&gamedata, sizeof(t_data));
	/*	
	if (parse_input(&gamedata.map_data, argc, argv))
		return(1); 
	*/
	parse_input(&gamedata.map_data, argc, argv);
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
	mlx_loop_hook(gamedata.window, &game_loop, &gamedata);
	printf("Window opened! Press ESC to close.\n");
	mlx_loop(gamedata.window);

	mlx_terminate(gamedata.window);
	return (EXIT_SUCCESS);
}
