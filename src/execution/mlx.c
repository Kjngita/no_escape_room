/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 08:57:42 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/03 15:59:13 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

static mlx_image_t	*load_gun(t_data *data, char *path, int width, int height)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(data->window, texture);
	mlx_delete_texture(texture);
	if (!image)
		return (NULL);
	mlx_resize_image(image, width, height);
	if (!image)
		return (mlx_delete_image(data->window, image), NULL);
	return (image);
}

void	init_images(t_data *data)
{
	data->img = mlx_new_image(data->window, WIDTH, HEIGHT);
	data->minimap = mlx_new_image(data->window, MINIMAP_SIDE, MINIMAP_SIDE);
	data->chaingun = load_gun(data, "./textures/chaingun_default.png", 650, 650);
	data->minimap->enabled = false;
	mlx_image_to_window(data->window, data->img, 0, 0);
	mlx_image_to_window(data->window, data->minimap, 50, 50);
	mlx_image_to_window(data->window, data->chaingun, (data->window->width / 2 - 325), (data->window->height - 650));
}


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
