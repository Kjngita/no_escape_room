#include "header_cub3d.h"

int	errmsg_n_retval(char *msg, int value)
{
	if (msg)
	{
		printf("Error\n");
		printf("%s\n", msg);
	}
	return (value);
}

int	main(int ac, char **av)
{
	t_mapstuff	map;
	if (ac < 2)
		return (errmsg_n_retval("No map provided", 1));
	if (ac > 2)
		return (errmsg_n_retval("Only 1 map at a time pls", 1));
	if (check_map_extension(av[1]) == -1)
		return (1);
	ft_bzero(&map, sizeof(t_mapstuff));
	map.Fcolor = -1;
	map.Ccolor = -1;
	if (map_content(&map, av[1]) == -1)
		return (1);
	return (0);
}

int	check_map_extension(char *map_name)
{
	int	extension;

	if (ft_strlen(map_name) < 4)
		return (errmsg_n_retval("Map name too short", -1));
	extension = ft_strlen(map_name) - 4;
	if (ft_strncmp(map_name + extension, ".cub", 5) != 0)
		return (errmsg_n_retval("Wrong map format", -1));
	return (0);
}

int	map_content(t_mapstuff *map, char *map_name)
{
	int	map_fd;

	map_fd = open(map_name, O_RDONLY);
	if (map_fd < 0)
		return (errmsg_n_retval("Cannot open map file", -1));
	// break_file_into_lines();
	return (0);

}

int	break_file_into_lines(t_mapstuff *map, int map_fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			return (errmsg_n_retval("Could not read map line", -1));
		// if (line_is_empty(map, line) == -1)
		// 	return (-1);
		free (line);
	}
	return (0);
}

// int	line_is_empty(t_mapstuff *map, char *line)
// {
// 	if (ft_strlen(line) == 1 && line[0] == '\n')
// 		return (0);
// }