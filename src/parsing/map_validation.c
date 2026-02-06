#include "header_cub3d.h"

int	map_valid(t_mapstuff *map, t_maplines *map_chain, size_t map_height)
{
	char	**testmap;

	if (!map->start_pos)
		return (errmsg_n_retval("No spawning orientation found", -1));
	testmap = ft_calloc(map_height + 1, sizeof (char *));
	if (!testmap)
		return (errmsg_n_retval("ft_calloc failed checking map", -1));
	if (copy_linkedlist_to_2xpointers(map_chain, testmap) == -1)
		return (-1);
	if (flood_fill(testmap, map->player_start_x, map->player_start_y,
		map_height) == -1)
	{
		testmap = clear_2x_char_pointers(testmap);
		return (errmsg_n_retval("Found black hole in map", -1));
	}
	testmap = clear_2x_char_pointers(testmap);
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

int	flood_fill(char **testmap, size_t x_coord, size_t y_coord,
	size_t map_height)
{
	char	tile;

	tile = testmap[y_coord][x_coord];
	if (tile == '1' || tile == 'F')
		return (0);
	if (y_coord == map_height - 1 || x_coord == 0
		|| will_fall_to_void(testmap, x_coord, y_coord))
		return (-1);
	testmap[y_coord][x_coord] = 'F';
	if (flood_fill(testmap, x_coord + 1, y_coord, map_height) == -1)
		return (-1);
	if (flood_fill(testmap, x_coord - 1, y_coord, map_height) == -1)
		return (-1);
	if (flood_fill(testmap, x_coord, y_coord + 1, map_height) == -1)
		return (-1);
	if (flood_fill(testmap, x_coord, y_coord - 1, map_height) == -1)
		return (-1);
	return (0);
}

int	will_fall_to_void(char **testmap, size_t x, size_t y)
{
	char	to_north;
	char	to_south;
	char	to_west;
	char	to_east;

	if (x > ft_strlen(testmap[y - 1]) || x > ft_strlen(testmap[y + 1]))
		return (1);
	to_north = testmap[y - 1][x];
	to_south = testmap[y + 1][x];
	to_west = testmap[y][x - 1];
	to_east = testmap[y][x + 1];
	if (to_north == ' ' || to_north == '\0' || to_south == ' '
		|| to_south == '\0' || to_west == ' ' || to_west == '\0'
		|| to_east == ' ' || to_east == '\0')
		return (1);
	return (0);
}
