/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:50:35 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/04 10:29:58 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

void	game_loop(void *param)
{
	t_data	*data;

	data = (t_data*)param;
	if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
		rotate(data, -1);
	if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
		rotate(data, 1);
	if (mlx_is_key_down(data->window, MLX_KEY_W))
		move_forward(data);
	if (mlx_is_key_down(data->window, MLX_KEY_S))
		move_backward(data);
	if (mlx_is_key_down(data->window, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(data->window, MLX_KEY_D))
		move_right(data);
	mouse_look(data);
	fill_background(data);
	cast_rays(data);
	draw_map(data);
}

int	main(int argc, char **argv)
{
	t_data	gamedata;

	ft_bzero(&gamedata, sizeof(t_data));
	if (parse_input(&gamedata.map_data, argc, argv))
		return (EXIT_FAILURE);
	calc_map_dimensions(&gamedata);
	calc_minimap_scaling(&gamedata);
	init_player_start(&gamedata);
	if (init_mlx(&gamedata))
		return (EXIT_FAILURE);
	mlx_key_hook(gamedata.window, &key_hook, &gamedata);
	mlx_resize_hook(gamedata.window, &resize_hook, &gamedata);
	mlx_loop_hook(gamedata.window, &game_loop, &gamedata);
	mlx_loop(gamedata.window);
	mlx_terminate(gamedata.window);
	wipe_map(&gamedata.map_data);
	return (EXIT_SUCCESS);
}
