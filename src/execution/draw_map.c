/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:04 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/30 17:20:24 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
! USED TO DRAW MINIMAP FIRST BUILD!
! NOT FULLY INTEGRATED TO SUPPORT VARIABLY SIZED PARSED MAPS AND
! NEEDS TO BE UPDATED BEFORE IT CAN BE USED TO DRAW FINAL MINIMAP!
*/

void draw_map(t_data *data)
{
	int			i;
	int 		j;
	int			x;
	int			y;
	uint32_t	color;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			if (data->map_data.dungeon[y][x] == '1')
				color = 0xFFFFFFFF;
			else
				color = 0x000000FF;
			i = 0;
			while (i < 64)
			{
				j = 0;
				while (j < 64)
				{
					mlx_put_pixel(data->img, (x * 64 + j), (y * 64 + i), color);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}
