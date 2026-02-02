/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:05:18 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/02 20:05:18 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
*UPDATE: now uses ceiling and floor colors parsed from map file
*UPDATE: now supports window resizing, by fetching screen height
*from mlx img data.
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

/*
*UPDATE: now supports window resizing, by fetching screen height
*from mlx img data.
*/

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

uint32_t	get_color(t_data *data, t_ray *ray, int tex_x, int tex_y)
{
	double	formula;

	formula = TILE_SIZE * tex_y + tex_x;
	if (ray->wall_face == NORTH)
	{
		
	}
	// 	return (N_COLOR);
	// if (ray->wall_face == SOUTH)
	// 	return(S_COLOR);
	// if (ray->wall_face == WEST)
	// 	return(W_COLOR);
	// if (ray->wall_face == EAST)
	// 	return (E_COLOR);
	// return (COLOR_MISSING);
}

void	find_wall_x(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->wall_x = data->pos_y + ray->wall_dist * ray->ray_dir_y;
		if (ray->wall_face == EAST)
			ray->wall_x = 1 - ray->wall_x;
	}
	else if (ray->side == 1)
	{
		ray->wall_x = data->pos_x + ray->wall_dist * ray->ray_dir_x;
		if (ray->wall_face == NORTH)
			ray->wall_x = 1 - ray->wall_x;
	}
}

void	draw_wall_line(t_data *data, t_ray *ray)
{
	uint32_t	color;
	int			tex_y;
	double		step;

	ray->texture_x = (int)(ray->wall_x * TILE_SIZE);
	step = 
	tex_y = ray->line_top;
	while (tex_y <= ray->line_bottom)
	{
		// draw_color = move pixel down the column by ratio according to 
		// the line/texture_height then pick the pixel color
		// mlx_put_pixel(data->img, ray->screen_x, y, draw_color);
		color = 
		tex_y++;
	}
}

