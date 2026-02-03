/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 08:57:42 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/03 10:38:09 by jjahkola         ###   ########.fr       */
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
		if (pressed_key.key == MLX_KEY_M)
		{
			data->mouse_look_enabled = !data->mouse_look_enabled;
			if (data->mouse_look_enabled == true)
				mlx_set_cursor_mode(data->window, MLX_MOUSE_HIDDEN);
			else
				mlx_set_cursor_mode(data->window, MLX_MOUSE_NORMAL);
		}
	}
}
