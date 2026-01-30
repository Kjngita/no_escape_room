/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:54:42 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/29 21:03:18 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
	All dir and plane values are initialized to 0 by default, and only changed
	by init_player_start when necessary.

	*UPDATE: Now gets initial facing and start location x y coordinates
	*from parsed data!
*/

void	init_player_start(t_data *data)
{
	char	facing;

	facing = data->map_data.start_pos;
	if (facing == 'N')
	{
		data->dir_y = -1;
		data->plane_x = 0.66;
	}
	if (facing == 'S')
	{
		data->dir_y = 1;
		data->plane_x = -0.66;
	}
	if (facing == 'W')
	{
		data->dir_x = -1;
		data->plane_y = -0.66;
	}
	if (facing == 'E')
	{
		data->dir_x = 1;
		data->plane_y = 0.66;
	}
	data->pos_x = (double)data->map_data.player_start_x + 0.5;
	data->pos_y = (double)data->map_data.player_start_y + 0.5;
}
