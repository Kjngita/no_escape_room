/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:58:54 by gita              #+#    #+#             */
/*   Updated: 2026/02/11 19:32:56 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
Start of process of parsing input file.
Register information provided in input file into the `t_mapstuff` struct.

Return: 0 on success, -1 on errors
*/
int	parse_input(t_mapstuff *map, int ac, char **av)
{
	if (ac < 2)
		return (errmsg_n_retval("No scene file provided", -1));
	if (ac > 2)
		return (errmsg_n_retval("Only 1 file at a time pls", -1));
	if (check_map_extension(av[1]) == -1)
		return (-1);
	map->floor_color = bitshift_rgba(0, 0, 0, 0);
	map->ceiling_color = bitshift_rgba(0, 0, 0, 0);
	if (map_content(map, av[1]) == -1)
	{
		wipe_map(map);
		return (-1);
	}
	return (0);
}

/*
(helper function of `parse_input()`)
Check input file extension.

Return: 0 on acceptable extension, -1 on errors
*/
int	check_map_extension(char *map_name)
{
	int	extension;

	if (!map_name)
		return (errmsg_n_retval("Could not see file name", -1));
	if (ft_strlen(map_name) < 4)
		return (errmsg_n_retval("File name too short", -1));
	extension = ft_strlen(map_name) - 4;
	if (ft_strncmp(map_name + extension, ".cub", 5) != 0)
		return (errmsg_n_retval("Wrong input file format", -1));
	return (0);
}

/*
(helper function of `parse_input()`)
- Open input file and allocate memory for first node of a linked list used to
construct the map
- Pass a string to helper function that extracts graphical elements to save the
content of the map's first line
- Pass the linked list of map lines, the string that holds content of the map's
first line, and the same fd (opened midway) to another helper function to build
the map
- Graphical elements and map will be registered into the `t_mapstuff` struct

Return: 0 on success, -1 on errors
*/
int	map_content(t_mapstuff *map, char *map_name)
{
	int			map_fd;
	char		*hotline;
	t_maplines	*map_chain;

	hotline = NULL;
	map_fd = open(map_name, O_RDONLY);
	if (map_fd < 0)
		return (errmsg_n_retval("Cannot open file", -1));
	map_chain = ft_calloc(1, sizeof(t_maplines));
	if (!map_chain)
	{
		close(map_fd);
		return (errmsg_n_retval("ft_calloc failed init mapchain", -1));
	}
	if (extract_graphics_elements(map, map_fd, &hotline) == -1)
	{
		free_n_nullify(&hotline);
		return (clear_maplines_close_fd_retval(map_chain, map_fd, -1));
	}
	if (extract_map(map, map_chain, map_fd, &hotline) == -1)
		return (clear_maplines_close_fd_retval(map_chain, map_fd, -1));
	return (clear_maplines_close_fd_retval(map_chain, map_fd, 0));
}

/*
(helper function of `extract_graphics_elements()`)
Check NO/SO/WE/EA textures and F/C colors.

Return: 1 if all graphical elements were registered, -1 if not
*/
int	got_all_elems(t_mapstuff *map)
{
	if (map->north_texture == NULL || map->south_texture == NULL
		|| map->west_texture == NULL || map->east_texture == NULL
		|| !color_alr_set(map->floor_color)
		|| !color_alr_set(map->ceiling_color))
		return (errmsg_n_retval("Not all graphics elements found", -1));
	if (map->north_texture->height != map->south_texture->height
		|| map->north_texture->height != map->west_texture->height
		|| map->north_texture->height != map->east_texture->height)
		return (errmsg_n_retval("Textures have different sizes", -1));
	return (1);
}
