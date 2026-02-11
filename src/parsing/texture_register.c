/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_register.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:48:53 by gita              #+#    #+#             */
/*   Updated: 2026/02/11 19:21:49 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
- Split the line by spaces and figure out the direction identifier
- Pass the `mlx_texture_t` pointer to helper function according to the direction 

Return: 0 on success, -1 on errors
*/
int	compass(t_mapstuff *map, char *line, int direction)
{
	char	**extract;
	int		check;

	check = 0;
	extract = ft_split(line, " ");
	if (!extract)
		return (errmsg_n_retval("ft_split failed in texture", -1));
	if (!extract[0] || !extract[1] || extract[2] != NULL)
	{
		extract = clear_2x_char_pointers(extract);
		return (errmsg_n_retval("Smt fishy ft_split setting texture", -1));
	}
	if (direction == NO)
		check = register_texture(&map->north_texture, extract[1]);
	else if (direction == SO)
		check = register_texture(&map->south_texture, extract[1]);
	else if (direction == WE)
		check = register_texture(&map->west_texture, extract[1]);
	else if (direction == EA)
		check = register_texture(&map->east_texture, extract[1]);
	extract = clear_2x_char_pointers(extract);
	return (check);
}

/*
(helper function of `compass()`)
- Check if this direction has already had a texture registered
- Check the path if file extension is correct
- Load the texture from PNG file

Return: 0 on success, -1 on errors
*/
int	register_texture(mlx_texture_t **wall_texture, char *path)
{
	if (*wall_texture)
		return (errmsg_n_retval("Duplicate texture registration", -1));
	if (!file_is_png(path))
		return (-1);
	*wall_texture = mlx_load_png(path);
	if (!*wall_texture)
		return (errmsg_n_retval("Failed to load png", -1));
	if ((*wall_texture)->height != (*wall_texture)->width)
		return (errmsg_n_retval("Not a square texture", -1));
	return (0);
}

/*
(helper function of `register_texture()`)
Check if texture file name is correct.

Return: 1 if file is ok, 0 if not
*/
int	file_is_png(char *path)
{
	if (!path)
		return (errmsg_n_retval("Could not see file path", 0));
	if (ft_strlen(path) < 4)
		return (errmsg_n_retval("Texture file name too short", 0));
	if (ft_strcmp(path + (ft_strlen(path) - 4), ".png"))
		return (errmsg_n_retval("Wrong texture file extension", 0));
	return (1);
}
