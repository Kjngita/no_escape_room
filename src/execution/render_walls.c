/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:05:18 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/30 11:24:30 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
*UPDATE: now uses ceiling and floor colors parsed from map file
*/

void	fill_background(t_data *data)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < data->img->width)
	{
		y = 0;
		while (y < data->img->height)
		{
			if (y < (data->img->height / 2))
				mlx_put_pixel(data->img, x, y, data->map_data.Ccolor);
			else
				mlx_put_pixel(data->img, x, y, data->map_data.Fcolor);
			y++;
		}
		x++;
	}
}

void	calc_line_height(t_data *data, t_ray *ray)
{
	int screen_height;
	int screen_center;

	screen_height = (int)data->img->height;
	screen_center = screen_height / 2;
	ray->line_height = (int)(screen_height / ray->wall_dist);
	ray->line_top = screen_center - (ray->line_height / 2);
	ray->line_bottom = screen_center + (ray->line_height / 2);
	if (ray->line_top < 0)
		ray->line_top = 0;
	if (ray->line_bottom >= screen_height)
		ray->line_bottom = screen_height - 1;
}

uint32_t	get_color(t_ray *ray)
{
	if (ray->wall_face == NORTH)
		return (N_COLOR);
	if (ray->wall_face == SOUTH)
		return(S_COLOR);
	if (ray->wall_face == WEST)
		return(W_COLOR);
	if (ray->wall_face == EAST)
		return (E_COLOR);
	return (COLOR_MISSING);
}

void	draw_wall_line(t_data *data, t_ray *ray)
{
	uint32_t	draw_color;
	int			y;

	draw_color = get_color(ray);
	y = ray->line_top;
	while (y <= ray->line_bottom)
	{
		mlx_put_pixel(data->img, ray->screen_x, y, draw_color);
		y++;
	}
}
