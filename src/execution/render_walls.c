
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

void	draw_wall_line(t_data *data, t_ray *ray)
{
	uint32_t	color;
	int			y;
	int			tex_y;
	double		tex_pos;
	double		ratio;

	ray->texture_x = (int)(ray->wall_x * data->map_data.EA_texture->width);
	ratio = (double)data->map_data.EA_texture->height / ray->line_height;
	tex_pos = (ray->line_top - data->window->height/2 + ray->line_height/2) 
		* ratio;
	y = ray->line_top;
	while (y <= ray->line_bottom)
	{
		tex_y = (int)tex_pos % data->map_data.EA_texture->height;
		color = get_color(data, ray, ray->texture_x, tex_y);
		mlx_put_pixel(data->img, ray->screen_x, y, color);
		tex_pos += ratio;
		y++;
	}
}

uint32_t	get_color(t_data *data, t_ray *ray, int tex_x, int tex_y)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	uint8_t			*pixel;

	texture = NULL;
	if (ray->wall_face == NORTH)
		texture = data->map_data.NO_texture;
	else if (ray->wall_face == SOUTH)
		texture = data->map_data.SO_texture;
	else if (ray->wall_face == WEST)
		texture = data->map_data.WE_texture;
	else if (ray->wall_face == EAST)
		texture = data->map_data.EA_texture;
	pixel = texture->pixels + ((tex_y * texture->height + tex_x) * texture->bytes_per_pixel);
	color = (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
	return (color);
}
