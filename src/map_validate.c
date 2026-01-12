#include "header_cub3d.h"

void	free_n_nullify(char **useless)
{
	if (*useless)
	{
		free (*useless);
		*useless = NULL;
	}
}

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

int	strlen_no_nl(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

int	got_all_elems(t_mapstuff *map, int map_fd)
{
	if (map->NOtexture == NULL || map->SOtexture == NULL
		|| map->WEtexture == NULL || map->EAtexture == NULL
		|| map->Fcolor == -1 || map->Ccolor == -1)
		return (errmsg_n_retval("Map starts too soon", -1));
	
	// how to know size of map to malloc??
	// mayb read until end and count, then another func to open map again?
	(void)map_fd;
	
	

	return (1);
}

