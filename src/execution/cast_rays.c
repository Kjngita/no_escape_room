/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:24:03 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/11 13:44:36 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
	Checks which block face the ray hits.
	
	side 0 = vertical wall
		step_x < 0 = ray moving left, hits E facing wall
		step_x > 0 = ray moving right, hits W facing wall
		
	side 1 (else)= horizontal wall
		step_y < 0 = ray moving up, hits S facing wall
		step_y > 0 = ray moving down, hits N facing wall
	
	Note! Y-coordinates are 'flipped' so 0 is up
*/

static void	check_face(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x < 0)
			ray->wall_face = EAST;
		else
			ray->wall_face = WEST;
	}
	else
	{
		if (ray->step_y < 0)
			ray->wall_face = SOUTH;
		else
			ray->wall_face = NORTH;
	}
}

static void	calc_wall_dist(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - data->pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->wall_dist = (ray->map_y - data->pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

//*Updated to use parsed map data

static void	cast_ray(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map_data.dungeon[ray->map_y][ray->map_x] != '0')
			hit = 1;
	}
}
/*
	Wrapper to handle ray initialization, casting, hit detection
	and rendering the actual wall column.

	One ray is cast per pixel of window width.
*/

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		i;

	i = 0;
	while (i < (int)data->img->width)
	{
		init_ray(data, &ray, i);
		cast_ray(data, &ray);
		check_face(&ray);
		calc_wall_dist(data, &ray);
		calc_line_height(data, &ray);
		find_wall_x(data, &ray);
		draw_wall_line(data, &ray);
		i++;
	}
}
