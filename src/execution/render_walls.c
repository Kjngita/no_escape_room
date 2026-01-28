/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:05:18 by jjahkola          #+#    #+#             */
/*   Updated: 2026/01/28 15:06:06 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

void	fill_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < (HEIGHT / 2))
				mlx_put_pixel(data->img, x, y, data->c_color);
			else
				mlx_put_pixel(data->img, x, y, data->f_color);
			y++;
		}
		x++;
	}
}

void	calc_line_height(t_ray *ray)
{
	int center;

	center = HEIGHT / 2;
	ray->line_height = (int)(HEIGHT / ray->wall_dist);
	ray->line_top = center - (ray->line_height / 2);
	ray->line_bottom = center + (ray->line_height / 2);
	if (ray->line_top < 0)
		ray->line_top = 0;
	if (ray->line_bottom >= HEIGHT)
		ray->line_bottom = HEIGHT - 1;
}

uint32_t	check_color(t_ray *ray)
{
	if (ray->side == 0) // vertical wall hit
	{
		if (ray->step_x < 0) //moved left, hit E facing wall
			return (E_COLOR);
		else
			return(W_COLOR); //moved right, hit W facing wall
	}
	// horizontal wall hit
	if (ray->step_y < 0) // moved up, hit S facing wall (Y coordinates flipped)
		return (S_COLOR);
	else
		return (N_COLOR); //moved down , hit N facing wall (Y coordinates flipped)
		
}

void	draw_wall_line(t_data *data, t_ray *ray)
{
	uint32_t	draw_color;
	int			y;

	draw_color = check_color(ray);
	y = ray->line_top;
	while (y <= ray->line_bottom)
	{
		mlx_put_pixel(data->img, ray->screen_x, y, draw_color);
		y++;
	}
}
