/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:23:09 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/11 14:00:22 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
! TO DO: Check resize fail!
*/

static void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;
	double	weapon_w_ratio;
	double	weapon_h_ratio;
	int		new_w;
	int		new_h;

	data = (t_data *)param;
	mlx_resize_image(data->img, width, height);
	//!CHECK RESIZE FAIL HERE!!
	mlx_delete_image(data->window, data->weapon);
	data->weapon = mlx_texture_to_image(data->window, data->weapon_texture);
	//!CHECK TEXTURE_TO_IMAGE FAIL HERE!!
	weapon_w_ratio = (double)WEAP_W / WIDTH;
	weapon_h_ratio = (double)WEAP_H / HEIGHT;
	new_w = width * weapon_w_ratio;
	new_h = height * weapon_h_ratio;
	mlx_image_to_window(data->window, data->weapon, (width / 2) - (new_w / 2),
		height - new_h);
	mlx_resize_image(data->weapon, new_w, new_h);
	//!CHECK RESIZE FAIL HERE!!
	data->weapon->instances[0].x = width / 2 - (new_w / 2);
	data->weapon->instances[0].y = height - new_h;
}

/*
*	Hook function to handle key press input. NOTE: cool bolean toggle
*	operator for toggling minimap visibility! This syntax switches
*	the boolean to whatever it is currently *not* :)
*/

static void	key_hook(mlx_key_data_t pressed_key, void *param)
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

void	register_hooks(t_data *data)
{
	mlx_key_hook(data->window, &key_hook, data);
	mlx_resize_hook(data->window, &resize_hook, data);
}
