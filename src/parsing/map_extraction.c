/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extraction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:39:22 by gita              #+#    #+#             */
/*   Updated: 2026/02/10 21:15:54 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
- Add each map line read from input file to the `t_maplines` list
- Validate if map is acceptable
- Convert the linked list of map lines into array of pointers and save in 
`t_mapstuff` struct

Return: 0 on success, -1 on errors
*/
int	extract_map(t_mapstuff *map, t_maplines *map_chain, int map_fd,
	char **map_1stline)
{
	size_t	line_no;

	line_no = 0;
	if (!*map_1stline)
		return (errmsg_n_retval("No map found", -1));
	if (add_to_flatmap(map_chain, map_1stline, line_no) == -1)
		return (-1);
	if (build_map_loop(map, map_chain, map_fd, &line_no) == -1)
		return (-1);
	if (map_valid(map, map_chain, line_no + 1) == -1)
		return (-1);
	return (0);
}

/*
(helper function of `extract_map()`)
Allocate a new node, ft_strdup the content of the line read from input file into
the node, and append the node to the `t_maplines` chain.

Return: 0 on success, -1 on errors
*/
int	add_to_flatmap(t_maplines *map_chain, char **line_to_add,
	size_t line_no)
{
	t_maplines	*new_node;
	t_maplines	*tail;

	if (line_no == 0)
	{
		map_chain->mapline = *line_to_add;
		map_chain->next = NULL;
		return (0);
	}
	new_node = ft_calloc(1, sizeof(t_maplines));
	if (!new_node)
		return (errmsg_n_retval("ft_calloc failed adding to flatmap", -1));
	new_node->mapline = ft_strdup(*line_to_add);
	if (!new_node->mapline)
	{
		free (new_node);
		return (errmsg_n_retval("ft_strdup failed adding to flatmap", -1));
	}
	new_node->next = NULL;
	tail = map_chain;
	while (tail->next)
		tail = tail->next;
	tail->next = new_node;
	return (0);
}

/*
(helper function of `extract_map()`)
- Read input file line by line (continue after the 1st line of the map)
- Check each line if acceptable as a map line

Return: 0 upon reaching eof, -1 on errors
*/
int	build_map_loop(t_mapstuff *map, t_maplines *map_chain, int map_fd,
	size_t *line_no)
{
	char	*line;
	int		eof;

	eof = 0;
	while (1)
	{
		line = get_next_line(map_fd, &eof);
		if (!line)
		{
			if (eof == 0)
				return (errmsg_n_retval("GNL failed extracting map", -1));
			break ;
		}
		line[strlen_no_nl(line)] = '\0';
		(*line_no)++;
		if (map_line_acceptable(map, map_chain, line, *line_no) == -1)
		{
			free_n_nullify(&line);
			return (-1);
		}
		free (line);
	}
	return (0);
}

/*
(helper function of `build_map_loop()`)
- Check if line is empty
- Check if line has allowed characters
- Register start position when seeing an identifier, then convert that position
to a normal tile
- Add the map line to the linked list

Return: 0 on success, -1 on errors
*/
int	map_line_acceptable(t_mapstuff *map, t_maplines *map_chain,
	char *line, size_t line_no)
{
	size_t	i;

	i = 0;
	if (line_is_empty(line))
		return (errmsg_n_retval("No empty line in map pls", -1));
	while (line[i])
	{
		if (ft_strchr("NSWE 01", line[i]) == NULL)
			return (errmsg_n_retval("Map line: Foreign character", -1));
		if (ft_isalpha(line[i]))
		{
			if (start_pos_setup(map, line[i], i, line_no) == -1)
				return (-1);
			line[i] = '0';
		}
		i++;
	}
	if (add_to_flatmap(map_chain, &line, line_no) == -1)
		return (-1);
	return (0);
}

/*
(helper function of `map_line_acceptable()`)
Register the player initial position (direction and coordinates)

Return: 0 on success, -1 on error
*/
int	start_pos_setup(t_mapstuff *map, char direction, size_t x_coord,
	size_t y_coord)
{
	if (map->start_pos != 0)
		return (errmsg_n_retval("Only 1 spawning orientation pls", -1));
	else
	{
		map->start_pos = direction;
		map->player_start_x = x_coord;
		map->player_start_y = y_coord;
		return (0);
	}
}
