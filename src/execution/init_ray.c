/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:26:38 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/28 14:24:39 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"


/*
Initializes delta distances for a ray (the diagonal distance a ray needs
to travel to cross a full grid square)
If x or y dir is 0, the corresponding delta is set to an unreachable value
*/

static void	init_deltas(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_x = HUGE_DELTA;
	else
		ray->delta_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_y = HUGE_DELTA;
	else
		ray->delta_y = fabs(1.0 / ray->ray_dir_y);
}

static void	init_steps(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

/*
Initializes distance to first x and y gridlines to cross.
*/

static void	init_side_dist(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
		ray->side_dist_x = (data->pos_x - ray->map_x) * ray->delta_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - data->pos_x) * ray->delta_x;
	if (ray->ray_dir_y < 0)
		ray->side_dist_y = (data->pos_y - ray->map_y) * ray->delta_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - data->pos_y) * ray->delta_y;
}

/*
Initializes variable values of a new ray
*/

void	init_ray(t_data *data, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / WIDTH - 1;
	ray->ray_dir_x = data->dir_x + (data->plane_x * ray->camera_x);
	ray->ray_dir_y = data->dir_y + (data->plane_y * ray->camera_x);
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	init_deltas(ray);
	init_steps(ray);
	init_side_dist(data, ray);
	ray->wall_dist = 0;
	ray->side = 0;
	ray->screen_x = x;
}
