/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:04 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/02 21:43:53 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

static void	draw_player(t_data *data)
{
	int	draw_start_x;
	int	draw_start_y;
	int	i;
	int	j;

	draw_start_x = (data->pos_x * 10) - 1;
	draw_start_y = (data->pos_y * 10) - 1;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(data->minimap, draw_start_x + j, draw_start_y + i, 0xFF000DFF);
			j++;
		}
		i++;
	}
	
}

/*
*	UPDATE: Modified function to use parsed map data, with varying
*	map heights and widths. Walls white, floors black, whitespace skipped
*/

void draw_map(t_data *data)
{
	int			i;
	int 		j;
	int			x;
	int			y;
	uint32_t	color;
	char		**map = data->map_data.dungeon;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '1')
				color = 0xFFFFFF80;
			else if (map[y][x] == '0')
				color = 0x00000080;
			else
			{
				x++;
				continue;
			}
			i = 0;
			while (i < 10)
			{
				j = 0;
				while (j < 10)
				{
					mlx_put_pixel(data->minimap, (x * 10 + j), (y * 10 + i), color);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
	draw_player (data);
}

