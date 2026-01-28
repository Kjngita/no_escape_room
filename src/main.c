/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:50:35 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/28 15:40:30 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

void	open_window(t_data *data)
{
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

int main(void)
{
	t_data	*gamedata;

	// initializes pos to center of screen, facing north (up)
	gamedata = ft_calloc(1, sizeof(t_data));
	gamedata->pos_x = 5.0;
	gamedata->pos_y = 5.0;
	init_facing(gamedata, 'E');
	init_map(gamedata);

	// 1. Initialize MLX (Width, Height, Title, Resizeable)
	open_window(gamedata);
	if (!gamedata->window)
	{
		// MLX42 has a built-in error string function
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	gamedata->img = mlx_new_image(gamedata->window, WIDTH, HEIGHT);
	mlx_image_to_window(gamedata->window, gamedata->img, 0, 0);
	// 2. Register the key hook
	// We pass 'mlx' as the parameter so we can use it in the function
	mlx_key_hook(gamedata->window, &key_hook, gamedata);
	mlx_loop_hook(gamedata->window, &game_loop, gamedata);
	// 3. Start the application loop
	printf("Window opened! Press ESC to close.\n");
	mlx_loop(gamedata->window);

	// 4. Cleanup memory
	mlx_terminate(gamedata->window);
	return (EXIT_SUCCESS);
}
/*
Facing direction cheat sheet:

Start Direction	dir_x	dir_y	plane_x	plane_y
North (N)		0		-1		0.66	0
South (S)		0		1		-0.66	0
West (W)		-1		0		0		-0.66
East (E)		1		0		0		0.66
*/