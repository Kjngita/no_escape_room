/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:54:42 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/29 15:44:00 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
	All dir and plane values are initialized to 0 by default, and only changed
	by init_facing when necessary.
*/

void	init_facing(t_data *data, unsigned char facing)
{
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
}
//*UPDATE MAP DEPENDANCY!!!
void init_map(t_data *data)
{
	int x;
	int y;

	int temp_map[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			data->map[y][x] = temp_map[y][x];
			x++;
		}
		y++;
	}
}
