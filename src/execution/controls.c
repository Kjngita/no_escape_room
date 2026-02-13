/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:07:45 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/13 14:07:03 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
Function to rotate the player's viewpoint. 
Takes either 1 or -1 as an argument, where 1 rotates the viewpoint clockwise,
and -1 counter-clockwise. dir_x and dir_y correspond to coordinates on the
radius of a circle, so that the vector length of dir_x + dir_y remains constant.
*/

void	rotate(t_data *data, double dir)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(ROT_SPEED * dir)
		- data->dir_y * sin(ROT_SPEED * dir);
	data->dir_y = old_dir_x * sin(ROT_SPEED * dir)
		+ data->dir_y * cos(ROT_SPEED * dir);
	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(ROT_SPEED * dir)
		- data->plane_y * sin(ROT_SPEED * dir);
	data->plane_y = old_plane_x * sin(ROT_SPEED * dir)
		+ data->plane_y * cos(ROT_SPEED * dir);
}

void	move_forward(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->pos_x + data->dir_x * MOVE_SPEED;
	new_pos_y = data->pos_y + data->dir_y * MOVE_SPEED;
	if (data->map_data.dungeon[(int)new_pos_y][(int)data->pos_x] == '0')
		data->pos_y = new_pos_y;
	if (data->map_data.dungeon[(int)data->pos_y][(int)new_pos_x] == '0')
		data->pos_x = new_pos_x;
}

void	move_backward(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->pos_x - data->dir_x * MOVE_SPEED;
	new_pos_y = data->pos_y - data->dir_y * MOVE_SPEED;
	if (data->map_data.dungeon[(int)new_pos_y][(int)data->pos_x] == '0')
		data->pos_y = new_pos_y;
	if (data->map_data.dungeon[(int)data->pos_y][(int)new_pos_x] == '0')
		data->pos_x = new_pos_x;
}

/*
Uses plane_x and plane_y as direction to offset player position, because
the offset angle is perpendicular to view direction
*/

void	move_left(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->pos_x - data->plane_x * MOVE_SPEED;
	new_pos_y = data->pos_y - data->plane_y * MOVE_SPEED;
	if (data->map_data.dungeon[(int)new_pos_y][(int)data->pos_x] == '0')
		data->pos_y = new_pos_y;
	if (data->map_data.dungeon[(int)data->pos_y][(int)new_pos_x] == '0')
		data->pos_x = new_pos_x;
}

/*
Uses plane_x and plane_y as direction to offset player position, because
the offset angle is perpendicular to view direction
*/

void	move_right(t_data *data)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = data->pos_x + data->plane_x * MOVE_SPEED;
	new_pos_y = data->pos_y + data->plane_y * MOVE_SPEED;
	if (data->map_data.dungeon[(int)new_pos_y][(int)data->pos_x] == '0')
		data->pos_y = new_pos_y;
	if (data->map_data.dungeon[(int)data->pos_y][(int)new_pos_x] == '0')
		data->pos_x = new_pos_x;
}
