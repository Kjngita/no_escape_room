
#include "header_cub3d.h"

static void print_map(t_mapstuff *map)
{
	int i = 0;
	while (map->dungeon[i])
	{
		printf("%s\n", map->dungeon[i]);
		i++;
	}
}

//* UPDATE:renamed from main

int	parse_input(t_mapstuff *map, int ac, char **av)
{
	if (ac < 2)
		return (errmsg_n_retval("No scene file provided", 1));
	if (ac > 2)
		return (errmsg_n_retval("Only 1 file at a time pls", 1));
	if (check_map_extension(av[1]) == -1)
		return (1);
	map->Fcolor = bitshift_rgba(0, 0, 0, 0); //printf("F");color_alr_set(map.Fcolor);
	map->Ccolor = bitshift_rgba(0, 0, 0, 0); //printf("C");color_alr_set(map.Ccolor);
	if (map_content(map, av[1]) == -1)
	{
		wipe_map(map);
		return (1);
	}
	print_map(map);
	//wipe_map(map);
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

/*
*	UPDATES:
*	1.	Added cleanup if extract_graphics_elements fails
*	2.	Packed clear_maplines and close function calls into
*		return statements to save lines
*	3.	Moved map_chain allocation to after fd opening and
*		and added fd close on ft_calloc failure
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
		return (clear_maplines(map_chain), close(map_fd), -1);
	if (extract_map(map, map_chain, map_fd, &hotline) == -1)
		return (clear_maplines(map_chain), close(map_fd), -1);
	return (close(map_fd), clear_maplines(map_chain), 0); //needs to change
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
	if (map->NO_texture == NULL || map->SO_texture == NULL
		|| map->WE_texture == NULL || map->EA_texture == NULL
		|| !color_alr_set(map->Fcolor) || !color_alr_set(map->Ccolor))
		return (errmsg_n_retval("Map starts too soon", -1));
	return (1);
}

