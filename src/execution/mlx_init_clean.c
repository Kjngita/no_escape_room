/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 08:57:42 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/06 18:27:25 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

static mlx_image_t	*load_weapon(t_data *data, char *path, int width, int height)
{
	mlx_image_t		*image;

	data->weapon_texture = mlx_load_png(path);
	if (!data->weapon_texture)
		return (NULL);
	image = mlx_texture_to_image(data->window, data->weapon_texture);
	if (!image)
		return (NULL);
	if (!mlx_resize_image(image, width, height))
		return (mlx_delete_image(data->window, image), NULL);
	return (image);
}

static int	init_images(t_data *data)
{
	data->img = mlx_new_image(data->window, WIDTH, HEIGHT);
	data->minimap = mlx_new_image(data->window, MINIMAP_SIDE, MINIMAP_SIDE);
	data->weapon = load_weapon(data, "./textures/chaingun_01.png", WEAP_W, WEAP_H);
	if (!data->img || !data->minimap || !data->weapon)
		return (-1);
	data->minimap->enabled = false;
	if (mlx_image_to_window(data->window, data->img, 0, 0) < 0)
		return (-1);
	if (mlx_image_to_window(data->window, data->minimap, 50, 50) < 0)
		return (-1);
	if (mlx_image_to_window(data->window, data->weapon,
			((data->window->width / 2) - (WEAP_W / 2)), (data->window->height - WEAP_H)) < 0)
		return (-1);
	return (0);
}

int	clean_all(t_data *data)
{
	if (data->weapon_texture)
		mlx_delete_texture(data->weapon_texture);
	if (data->window)
		mlx_terminate(data->window);
	wipe_map(&data->map_data);
	return (-1);
}

int	init_mlx(t_data *data)
{
	data->window = mlx_init(WIDTH, HEIGHT, "Chaplin Moustache Hunting Club", true);
	if (!data->window)
	{
		ft_putstr_fd("Error\nFailed to initialize window", 2);
		return (clean_all(data));
	}
	mlx_set_cursor_mode(data->window, MLX_MOUSE_HIDDEN);
	if (init_images(data) < 0)
	{
		ft_putstr_fd("Error\nFailed to initialize graphics", 2);
		return (clean_all(data));
	}
	return (0);
}

