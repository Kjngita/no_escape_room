/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 10:23:09 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/11 16:13:52 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

static int	safe_resize_image(mlx_t *window, mlx_image_t *img,
	uint32_t w, uint32_t h)
{
	if (!mlx_resize_image(img, w, h))
	{
		printf("Error\nMLX image resize failure\n");
		mlx_close_window(window);
		return (-1);
	}
	return (0);
}

static int	safe_image_to_window(mlx_t *window, mlx_image_t *img,
	int32_t x, int32_t y)
{
	if (mlx_image_to_window(window, img, x, y) < 0)
	{
		printf("Error\nMLX image to window failure\n");
		mlx_close_window(window);
		return (-1);
	}
	return (0);
}

/*
	Handles resizing of the window and images. Because mlx_resize_image
	is destructive (pixel data is lost when scaling down), a new image is
	created from the texture file each time the weapon is resized. This 
	avoids image deterioration when scaling down and up again.
*/

static void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;
	int		new_w;
	int		new_h;

	data = (t_data *)param;
	if (safe_resize_image(data->window, data->img, width, height) < 0)
		return ;
	mlx_delete_image(data->window, data->weapon);
	data->weapon = mlx_texture_to_image(data->window, data->weapon_texture);
	if (!data->weapon)
	{
		printf("Error\nMLX texture to image failure\n");
		mlx_close_window(data->window);
		return ;
	}
	new_w = width * (double)WEAP_W / WIDTH;
	new_h = height * (double)WEAP_H / HEIGHT;
	if (new_w < 1)
		new_w = 1;
	if (new_h < 1)
		new_h = 1;
	if (safe_image_to_window(data->window, data->weapon,
			(width / 2) - (new_w / 2), height - new_h) < 0)
		return ;
	safe_resize_image(data->window, data->weapon, new_w, new_h);
}

/*
	Hook function to handle key press input.
	NOTE: cool bolean toggle operator for setting minimap visibility!
	This syntax switches the boolean to whatever it is currently *not* :)
	ALSO: player control key mapping is not done here, but in the game loop
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
