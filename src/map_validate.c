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
	{
		//cleanup
		return (1);
	}
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
	if (extract_graphics_elements(map, map_fd) == -1)
	{
		close (map_fd);
		return (-1);
	}
	close (map_fd);
	return (0);

}

int	extract_graphics_elements(t_mapstuff *map, int map_fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			return (errmsg_n_retval("Could not read map line", -1));
		if (line_is_empty(line))
		{
			free (line);
			continue ;
		}
		else if (line_is_start_of_map(map, line))
			return (got_all_elems(map));
		else if (line_has_info(map, line) == -1) //can't be first since strtrim
			return (-1);
		free (line);
	}
	return (0);
}

int	line_is_empty(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	return (0);
}

int	line_is_start_of_map(t_mapstuff *map, char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(" 1\n", line[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

int	got_all_elems(t_mapstuff *map)
{
	if (map->NOtexture == NULL || map->SOtexture == NULL
		|| map->WEtexture == NULL || map->EAtexture == NULL
		|| map->Fcolor == -1 || map->Ccolor == -1)
		return (errmsg_n_retval("Map starts too soon", -1));
	return (1);
}
int	line_has_info(t_mapstuff *map, char *line)
{
	size_t	i;

	i = 0;
	// if (ft_strtrim(line, " \t\n") == NULL)
	// 	return (errmsg_n_retval("strtrim failed", -1));
	// ft_split
	
	// is it NO SO WE EA
	// if (ft_strncmp(line, "NO", 2) == 0)
	// 	return (register_texture_NO(map, line)); //0 for normal registration
	// else if (ft_strncmp(line, "SO", 2) == 0)
	// 	return (register_texture_SO(map, line));
	// else if (ft_strncmp(line, "WE", 2) == 0)
	// 	return (register_texture_WE(map, line));
	// else if (ft_strncmp(line, "EA", 2) == 0)
	// 	return (register_texture_EA(map, line));
	
	// then is it color
	
	// else return (errmsg_n_retval("Weird line", -1));
	
	return (0); //for normal
}
