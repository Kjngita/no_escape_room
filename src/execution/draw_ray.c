/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:22:08 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/30 17:22:35 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
!	USED BY INITIAL RAY VISUALIZATION TEST, BUT CURRENTLY UNUSED!
!	WILL NEED TO BE REBUILT IF WE IMPLEMENT VIEW CONE VISUALIZATION
!	IN OUR MINIMAP VIEW
*/

static void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1)
	{
		// Boundary check before drawing
		if (x0 >= 0 && x0 < (int)img->width && y0 >= 0 && y0 < (int)img->height)
			mlx_put_pixel(img, x0, y0, 0xFF0000FF);

		if (x0 == x1 && y0 == y1) break;
		
		e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x0 += sx; }
		if (e2 < dx)  { err += dx; y0 += sy; }
	}
}

/*
!	USED BY INITIAL RAY VISUALIZATION TEST, BUT CURRENTLY UNUSED!
!	WILL NEED TO BE REBUILT IF WE IMPLEMENT VIEW CONE VISUALIZATION
!	IN OUR MINIMAP VIEW
*/

void	draw_ray(t_data *data, t_ray *ray, mlx_image_t *img)
{
	double current_dist;

	// 1. Recover the exact Euclidean distance from the DDA variables
	if (ray->side == 0)
		current_dist = ray->side_dist_x - ray->delta_x;
	else
		current_dist = ray->side_dist_y - ray->delta_y;

	// 2. Calculate coordinates
	int start_x = (int)(data->pos_x * TILE_SIZE);
	int start_y = (int)(data->pos_y * TILE_SIZE);

	int end_x = (int)((data->pos_x + ray->ray_dir_x * current_dist) * TILE_SIZE);
	int end_y = (int)((data->pos_y + ray->ray_dir_y * current_dist) * TILE_SIZE);

	draw_line(img, start_x, start_y, end_x, end_y);
}
