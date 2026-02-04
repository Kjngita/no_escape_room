/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:54:42 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/04 14:22:50 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
	Calculates map dimensions, for determining minimap tile size
*/

static void	calc_map_dimensions(t_data *data)
{
	int		x;
	int		y;
	int		max_x;
	char	**map;
	
	y = 0;
	max_x = 0;
	map = data->map_data.dungeon;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
			x++;
		if (x > max_x)
			max_x = x;
		y++;
	}
	data->map_data.map_width = max_x;
	data->map_data.map_height = y;
}

/*
	Calculates size to draw minimap tiles, so the finished map
	fits into a MINIMAP_SIDE * MINIMAP_SIDE square. If the minimum
	tile size of 1 px is reached, will draw beyond square limits.
	For tiny maps, will still not draw tiles larger than set limit.
*/

static void	calc_minimap_scaling(t_data *data)
{
	double	x_max_tile_size;
	double	y_max_tile_size;
	int		max_tile_size_rounded;
	
	x_max_tile_size = MINIMAP_SIDE / data->map_data.map_width;
	y_max_tile_size = MINIMAP_SIDE / data->map_data.map_height;
	if (x_max_tile_size < y_max_tile_size)
		max_tile_size_rounded = (int)x_max_tile_size;
	else
		max_tile_size_rounded = (int)y_max_tile_size;
	if (max_tile_size_rounded > 25)
		max_tile_size_rounded = 25;
	if (max_tile_size_rounded == 0)
		max_tile_size_rounded = 1;
	data->map_data.minimap_tile_size = max_tile_size_rounded;
}

/*
	All dir and plane values are initialized to 0 by default, and only changed
	by init_player_start when necessary.

	*UPDATE: Now gets initial facing and start location x y coordinates
	*from parsed data!
*/

static void	init_player_start(t_data *data)
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

/*
	Wrapper function.
!	TO DO? Error checking? Program should have already exited if any data
!	dependencies are broken, but maybe for extra security..?
*/

void	init_start_vars(t_data *data)
{
	calc_map_dimensions(data);
	calc_minimap_scaling(data);
	init_player_start(data);
}
