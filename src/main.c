/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:50:35 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/11 10:44:21 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

static void	game_loop(void *param)
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

static void	start_game(t_data *data)
{
	mlx_loop_hook(data->window, &game_loop, data);
	mlx_loop(data->window);
}

/*
!	TO DO: CHECK HOW TO PROPAGATE WEAPON RESIZE ERROR UP THE CALL CHAIN!
!	DOES start_game RUN IF WINDOW HAS BEEN CLOSED FOLLOWING ERROR IN
!	register_hooks COMPONENTS?
*/

int	main(int argc, char **argv)
{
	t_data	gamedata;

	ft_bzero(&gamedata, sizeof(t_data));
	if (parse_input(&gamedata.map_data, argc, argv))
		return (EXIT_FAILURE);
	init_start_vars(&gamedata);
	if (init_mlx(&gamedata))
		return (EXIT_FAILURE);
	register_hooks(&gamedata);
	start_game(&gamedata);
	clean_all(&gamedata);
	return (EXIT_SUCCESS);
}
