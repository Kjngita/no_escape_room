#include "header_cub3d.h"

int	extract_map(t_mapstuff *map, int map_fd, char *map_1stline)
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
		if (map_line_acceptable(map, line) == -1)
			return (-1);
		add_to_flatmap(map->flatmap, line);
		free (line);
	}
	if (!map->orientation)
		return (errmsg_n_retval("No spawning orientation found", -1));
	return (0);
}

int	map_line_acceptable(t_mapstuff *map, char *line)
{
	size_t	i;

	i = 0;
	if (line_is_empty(line))
		return (errmsg_n_retval("No empty line in map pls", -1));
	while (line[i])
	{
		if (ft_strchr("NSWE 01", line[i]) == NULL)
			return (errmsg_n_retval("Map line: Foreign character", -1));
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E')
		{
			if (orientation_setup(map, line, line[i]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	orientation_setup(t_mapstuff *map, char *line, char	direction)
{
	if (map->orientation != 0)
		return (errmsg_n_retval("Only 1 spawning orientation pls", -1));
	else
	{
		map->orientation = direction;
		return (0);
	}
}

int	add_to_flatmap(t_maplines *map, char *mapline)
{

}
