#include "header_cub3d.h"

int	extract_map(t_mapstuff *map, t_maplines *map_chain, int map_fd,
	char **map_1stline)
{
	char	*line;
	int		eof;
	size_t	line_no;

	eof = 0;
	line_no = 0;
	add_to_flatmap(map_chain, map_1stline, line_no);
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
		line_no++;
		if (map_line_acceptable(map, map_chain, line, line_no) == -1)
			return (-1);
		free (line);
	}
	if (map_valid(map, map_chain, line_no + 1) == -1)
		return (-1);
	return (0);
}

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
		}
		i++;
	}
	add_to_flatmap(map_chain, &line, line_no);
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
		return (errmsg_n_retval("ft_strdup failed adding to flatmap", -1));
	new_node->next = NULL;
	tail = map_chain;
	while (tail->next)
		tail = tail->next;
	tail->next = new_node;
	return (0);
}

int	map_valid(t_mapstuff *map, t_maplines *map_chain, size_t map_height)
{
	char	**testmap;
	int		hole;

	if (!map->start_pos)
		return (errmsg_n_retval("No spawning orientation found", -1));
	testmap = ft_calloc(map_height + 1, sizeof (char *));
	if (!testmap)
		return (errmsg_n_retval("ft_calloc failed checking map", -1));
	if (copy_linkedlist_to_2xpointers(map_chain, testmap) == -1)
		return (-1);
	hole = 0;
	flood_fill(testmap, map->player_start_x, map->player_start_y, &hole);
	if (hole == 1)
	{
		testmap = clear_2x_char_pointers(testmap);
		return (errmsg_n_retval("Found black hole in map", -1));
	}
	testmap = clear_2x_char_pointers(testmap); printf("✅ Map okay\n");
	map->dungeon = ft_calloc(map_height + 1, sizeof (char *));
	if (!map->dungeon)
		return (errmsg_n_retval("ft_calloc failed creating map", -1));
	if (copy_linkedlist_to_2xpointers(map_chain, map->dungeon) == -1)
		return (-1);
	return (0);
}

int	copy_linkedlist_to_2xpointers(t_maplines *map_chain, char **dest)
{
	t_maplines	*copy;
	size_t		i;

	i = 0;
	copy = map_chain;
	while (copy)
	{
		dest[i] = ft_strdup(copy->mapline);
		if (!dest[i])
		{
			dest = clear_2x_char_pointers(dest);
			return (errmsg_n_retval("ft_strdup failed ll->2xp", -1));
		}
		i++;
		copy = copy->next;
	}
	dest[i] = NULL;
	return (0);
}

void	flood_fill(char **testmap, size_t x_coord, size_t y_coord, int *hole)
{
	char	tile;

	tile = testmap[y_coord][x_coord];
	if (tile == '1' || tile == 'F' || *hole == 1)
		return ;
	if (tile == ' ')
	{
		*hole = 1;
		return ;
	}
	testmap[y_coord][x_coord] = 'F';
	flood_fill(testmap, x_coord + 1, y_coord, hole);
	flood_fill(testmap, x_coord - 1, y_coord, hole);
	flood_fill(testmap, x_coord, y_coord + 1, hole);
	flood_fill(testmap, x_coord, y_coord - 1, hole);
}
