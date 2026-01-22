#include "header_cub3d.h"

int	extract_map(t_mapstuff *map, int map_fd, char **map_1stline, size_t *line_no)
{
	char	*line;
	int		eof;

	eof = 0;
	add_to_flatmap(map, map_1stline, *line_no);
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
		*(line_no)++;
		if (map_line_acceptable(map, line, *line_no) == -1)
			return (-1);
		free (line);
	}
	if (!map->start_pos)
		return (errmsg_n_retval("No spawning orientation found", -1));
	return (0);
}

int	map_line_acceptable(t_mapstuff *map, char *line, size_t line_no)
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
		}
		i++;
	}
	add_to_flatmap(map, &line, line_no);
	return (0);
}

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

int	add_to_flatmap(t_mapstuff *map, char **line_to_add, size_t line_no)
{
	t_maplines	*new_node;
	t_maplines	*tail;

	new_node = ft_calloc(1, sizeof(t_maplines));
	if (!new_node)
		return (errmsg_n_retval("ft_calloc failed adding to flatmap", -1));
	if (line_no == 0)
		new_node->mapline = *line_to_add;
	else
	{
		new_node->mapline = ft_strdup(*line_to_add);
		if (!new_node->mapline)
			return (errmsg_n_retval("ft_strdup failed adding to flatmap", -1));
	}
	new_node->next = NULL;
	if (!map->flatmap)
		map->flatmap = new_node;
	else
	{
		tail = map->flatmap;
		while (tail->next)
			tail = tail->next;
		tail->next = new_node;
	}
	return (0);
}

int	map_valid(t_mapstuff *map, size_t map_height)
{
	char	**testmap;

	testmap = ft_calloc(map_height, sizeof (char *));
	if (!testmap)
		return (errmsg_n_retval("ft_calloc failed checking map", -1));
	copy_linkedlist_to_2xpointers(map, testmap);
	size_t i = 0;
	while (i < map_height)
		printf("%s\n", testmap[i++]);
	return (0);
}

int	copy_linkedlist_to_2xpointers(t_mapstuff *map, char **dest)
{
	t_maplines	*copy;
	size_t		i;

	i = 0;
	copy = map->flatmap;
	while (copy)
	{
		dest[i] = ft_strdup(copy->mapline);
		if (!dest[i])
		{
			dest = clear_2x_char_pointers(dest);
			return (errmsg_n_retval("ft_strdup failed ll->2xp", -1));
		}
		i++;
		copy = map->flatmap->next;
	}
	return (0);
}
