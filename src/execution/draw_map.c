/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:04 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/04 11:08:04 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

static void	draw_player(t_data *data)
{
	int	draw_start_x;
	int	draw_start_y;
	int	i;
	int	j;
	int	tile;

	tile = data->map_data.minimap_tile_size;
	draw_start_x = (data->pos_x * tile) - (tile / 4);
	draw_start_y = (data->pos_y * tile) - (tile / 4);
	i = 0;
	while (i < tile / 2)
	{
		j = 0;
		while (j < tile / 2)
		{
			mlx_put_pixel(data->minimap, draw_start_x + j, draw_start_y + i, 0xFF000DFF);
			j++;
		}
		i++;
	}
}

/*
	Called by draw_map to draw a single map tile per function call
*/

static void	draw_tile(t_data *data, int x, int y)
{
	int			i;
	int			j;
	int			tile;
	uint32_t	color;

	i = 0;
	tile = data->map_data.minimap_tile_size;
	if (data->map_data.dungeon[y][x] == '1')
		color = 0xFFFFFF80;
	else
		color = 0x00000080;
	while (i < tile)
	{
		j = 0;
		while (j < tile)
		{
			mlx_put_pixel(data->minimap, (x * tile + j), (y * tile + i), color);
			j++;
		}
		i++;
	}
}

/*
	UPDATE: Modified function to use parsed map data, with varying
	map heights and widths. Walls white, floors black, whitespace skipped
*	UPDATE: Split draw tile into separate function for norm compliance
*/

void draw_map(t_data *data)
{
	int			x;
	int			y;

	y = 0;
	while (data->map_data.dungeon[y] != NULL)
	{
		x = 0;
		while (data->map_data.dungeon[y][x] != '\0')
		{
			if (data->map_data.dungeon[y][x] == '1'
					|| data->map_data.dungeon[y][x] == '0')
				draw_tile(data, x, y);
			x++;
		}
		y++;
	}
	draw_player(data);
}
