/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:24:03 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/28 15:04:23 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

static void	calc_wall_dist(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - data->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->wall_dist = (ray->map_y - data->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

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
			ray->side = 0; //hit vertical (x) grid line
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1; //hit horizontal (y) grid line
		}
		if (data->map[ray->map_y][ray->map_x] != 0)
			hit = 1;
	}
}

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		i;
	
	i = 0;
	while (i < WIDTH)
	{
		init_ray(data, &ray, i);
		cast_ray(data, &ray);
		calc_wall_dist(data, &ray);
		calc_line_height(&ray);
		//draw_ray(data, &ray, data->img);
		draw_wall_line(data, &ray);
		i++;
	}
}
