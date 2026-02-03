/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:03:04 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/03 15:11:04 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

void	calc_map_dimensions(t_data *data)
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

void	calc_minimap_scaling(t_data *data)
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
	if (max_tile_size_rounded == 0)
		max_tile_size_rounded = 1; 
	data->map_data.minimap_tile_size = max_tile_size_rounded;
}

static void	draw_player(t_data *data)
{
	int	draw_start_x;
	int	draw_start_y;
	int	i;
	int	j;
	int	tile;

	tile = data->map_data.minimap_tile_size;
	draw_start_x = (data->pos_x * tile) - 1;
	draw_start_y = (data->pos_y * tile) - 1;
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
	int			tile;
	char		**map;
	
	map = data->map_data.dungeon;
	tile = data->map_data.minimap_tile_size;
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
			x++;
		}
		y++;
	}
	draw_player (data);
}

/*
void	calc_map_dimensions(t_data *data)
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

void	calc_minimap_scaling(t_data *data)
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
	data->map_data.minimap_tile_size = max_tile_size_rounded;
}

static void	draw_player(t_data *data)
{
	int	draw_start_x;
	int	draw_start_y;
	int	i;
	int	j;
	//int	tile;

	//tile = data->map_data.minimap_tile_size;
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

*	UPDATE: Modified function to use parsed map data, with varying
*	map heights and widths. Walls white, floors black, whitespace skipped

void draw_map(t_data *data)
{
	int			i;
	int 		j;
	int			x;
	int			y;
	uint32_t	color;
	int			tile;
	char		**map;
	
	map = data->map_data.dungeon;
	tile = data->map_data.minimap_tile_size;
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
*/