
#include "header_cub3d.h"

// static void print_map(t_mapstuff *map)
// {
// 	t_maplines	*print;
// 	print = map->flatmap;
// 	while (print)
// 	{
// 		printf("%s\n", print->mapline);
// 		print = print->next;
// 	}
// }

int	main(int ac, char **av)
{
	t_mapstuff	map;

	if (ac < 2)
		return (errmsg_n_retval("No scene file provided", 1));
	if (ac > 2)
		return (errmsg_n_retval("Only 1 file at a time pls", 1));
	if (check_map_extension(av[1]) == -1)
		return (1);
	ft_bzero(&map, sizeof(t_mapstuff));
	map.Fcolor = bitshift_rgba(0, 0, 0, 0); //printf("F");color_alr_set(map.Fcolor);
	map.Ccolor = bitshift_rgba(0, 0, 0, 0); //printf("C");color_alr_set(map.Ccolor);
	if (map_content(&map, av[1]) == -1)
	{
		wipe_map(&map);
		return (1);
	}
	// print_map(&map);
	wipe_map(&map);
	return (0);
}

int	check_map_extension(char *map_name)
{
	int	extension;

	if (!map_name)
		return (errmsg_n_retval("Could not see file name", -1));
	if (ft_strlen(map_name) < 4)
		return (errmsg_n_retval("File name too short", -1));
	extension = ft_strlen(map_name) - 4;
	if (ft_strncmp(map_name + extension, ".cub", 5) != 0)
		return (errmsg_n_retval("Wrong file format", -1));
	return (0);
}

int	map_content(t_mapstuff *map, char *map_name)
{
	int		map_fd;
	char	*hotline;
	size_t	line_no;

	hotline = NULL;
	line_no = 0;
	map_fd = open(map_name, O_RDONLY);
	if (map_fd < 0)
		return (errmsg_n_retval("Cannot open file", -1));
	if (extract_graphics_elements(map, map_fd, &hotline) == -1)
	{
		close (map_fd);
		return (-1);
	}
	if (extract_map(map, map_fd, &hotline, &line_no) == -1)
	{
		close (map_fd);
		return (-1);
	}
	close (map_fd);
	map_valid(map, line_no + 1);
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

int	got_all_elems(t_mapstuff *map)
{
	if (map->NOtexture == NULL || map->SOtexture == NULL
		|| map->WEtexture == NULL || map->EAtexture == NULL
		|| !color_alr_set(map->Fcolor) || !color_alr_set(map->Ccolor))
		return (errmsg_n_retval("Map starts too soon", -1));
	printf("Checking elems:\nN: %s\nS: %s\nW: %s\nE: %s\n", map->NOtexture, map->SOtexture, map->WEtexture, map->EAtexture);printf("F:%i\nC:%i\n", map->Fcolor, map->Ccolor);
	return (1);
}

