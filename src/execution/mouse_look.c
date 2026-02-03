/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_look.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 08:56:22 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/03 10:34:47 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

void	mouse_look(t_data *data)
{
	int32_t	x;
	int32_t	y;
	int			center_x;
	int			delta_x;

	if (data->mouse_look_enabled)
	{
		center_x = data->window->width / 2;
		mlx_get_mouse_pos(data->window, &x, &y);
		delta_x = x - center_x;
		if (delta_x != 0)
		{
			rotate(data, delta_x * MOUSE_SENSITIVITY);
			mlx_set_mouse_pos(data->window, center_x, data->window->height / 2);
		}
	}
}
