/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:23:09 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/04 10:24:05 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
! TO DO: Check resize fail!
*/

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
			data->cursor_enabled = !data->cursor_enabled;
			if (data->cursor_enabled == true)
				mlx_set_cursor_mode(data->window, MLX_MOUSE_NORMAL);
			else
				mlx_set_cursor_mode(data->window, MLX_MOUSE_HIDDEN);
		}
	}
}
