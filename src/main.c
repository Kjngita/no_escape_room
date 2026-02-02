/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:50:35 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/02 22:00:17 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

void	mouse_look(t_data *data)
{
	int32_t	x;
	int32_t	y;
	int			center_x;
	int			delta_x;

	center_x = data->window->width / 2;
	mlx_get_mouse_pos(data->window, &x, &y);
	delta_x = x - center_x;
	if (delta_x != 0)
	{
		rotate(data, delta_x * MOUSE_SENSITIVITY);
		mlx_set_mouse_pos(data->window, center_x, data->window->height / 2);
	}
}

void	open_window(t_data *data)
{
	// 1. Initialize MLX (Width, Height, Title, Resizeable)
	data->window = mlx_init(WIDTH, HEIGHT, "Chaplin Moustache Hunting Club", true);
	/*
	if (!data->window)
		cleanup function
	*/
	mlx_set_cursor_mode(data->window, MLX_MOUSE_HIDDEN);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data *data;
	
	data = (t_data*)param;
	mlx_resize_image(data->img, width, height);
}

/*
*	Hook function to handle key press input. NOTE: cool bolean toggle
*	operator for toggling minimap visibility! This syntax switches
*	the boolean to whatever it is currently *not* :)
*/

void	key_hook(mlx_key_data_t pressed_key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (pressed_key.action == MLX_PRESS || pressed_key.action == MLX_REPEAT)
	{
		if (pressed_key.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->window);
		if (pressed_key.key == MLX_KEY_TAB)
			data->minimap->enabled = !data->minimap->enabled;
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
	init_player_start(&gamedata);
	open_window(&gamedata);
	if (!gamedata.window)
	{
		// MLX42 has a built-in error string function
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
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
