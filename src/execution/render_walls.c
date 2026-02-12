/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:00:34 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/12 16:48:52 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

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
				mlx_put_pixel(data->img, x, y, data->map_data.ceiling_color);
			else
				mlx_put_pixel(data->img, x, y, data->map_data.floor_color);
			y++;
		}
		x++;
	}
}

void	calc_line_height(t_data *data, t_ray *ray)
{
	int	screen_height;
	int	screen_center;

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

/*
Find where on the x-axis of the wall the ray hits based on the ray direction
(W/E or N/S wall hit), take only the decimal part, mirror if wall is facing
E or N
*/
void	find_wall_x(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->wall_x = data->pos_y + ray->wall_dist * ray->ray_dir_y;
		ray->wall_x -= floor(ray->wall_x);
		if (ray->wall_face == EAST)
			ray->wall_x = 1 - ray->wall_x;
	}
	else if (ray->side == 1)
	{
		ray->wall_x = data->pos_x + ray->wall_dist * ray->ray_dir_x;
		ray->wall_x -= floor(ray->wall_x);
		if (ray->wall_face == NORTH)
			ray->wall_x = 1 - ray->wall_x;
	}
}

/*
- Find where on the x-axis of the texture the ray hits based on wall_x
- Calculate the "distance" to move down the texture to pick the corresponding
pixel when drawing the line
- Find where to start picking color from the texture (especially when not all
of the wall is visible)
- Start at top of wall line, moving 1 pixel down at a time until hitting line
bottom, pick color from the texture accordingly and draw that pixel on screen
*/
void	draw_wall_line(t_data *data, t_ray *ray)
{
	uint32_t	color;
	int			y;
	int			tex_y;
	double		tex_pos;
	double		ratio;

	ray->texture_x = (int)(ray->wall_x * data->map_data.east_texture->width);
	ratio = (double)data->map_data.east_texture->height / ray->line_height;
	tex_pos = (ray->line_top - data->window->height / 2 + ray->line_height / 2)
		* ratio;
	y = ray->line_top;
	while (y <= ray->line_bottom)
	{
		tex_y = (int)tex_pos % data->map_data.east_texture->height;
		color = get_color(data, ray, ray->texture_x, tex_y);
		mlx_put_pixel(data->img, ray->screen_x, y, color);
		tex_pos += ratio;
		y++;
	}
}

/*
(helper function of `draw_wall_line()`)
Get the color data from the texture.
Move the pointer *pixel along the array of the texture's pixel data to the point
where the wanted pixel's color info is stored, then convert 4 uint8_t numbers
which are RGBA values of that pixel into one return value.

Return: An uint32_t number that has (r | g | b | a) info of a color
*/
uint32_t	get_color(t_data *data, t_ray *ray, int tex_x, int tex_y)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	uint8_t			*pixel;

	texture = NULL;
	if (ray->wall_face == NORTH)
		texture = data->map_data.north_texture;
	else if (ray->wall_face == SOUTH)
		texture = data->map_data.south_texture;
	else if (ray->wall_face == WEST)
		texture = data->map_data.west_texture;
	else if (ray->wall_face == EAST)
		texture = data->map_data.east_texture;
	pixel = texture->pixels + ((tex_y * texture->height + tex_x)
			* texture->bytes_per_pixel);
	color = bitshift_rgba(pixel[0], pixel[1], pixel[2], pixel[3]);
	return (color);
}
