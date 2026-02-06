
#include "header_cub3d.h"

//* UPDATE:renamed from main

int	parse_input(t_mapstuff *map, int ac, char **av)
{
	if (ac < 2)
		return (errmsg_n_retval("No scene file provided", 1));
	if (ac > 2)
		return (errmsg_n_retval("Only 1 file at a time pls", 1));
	if (check_map_extension(av[1]) == -1)
		return (1);
	map->Fcolor = bitshift_rgba(0, 0, 0, 0);
	map->Ccolor = bitshift_rgba(0, 0, 0, 0);
	if (map_content(map, av[1]) == -1)
	{
		wipe_map(map);
		return (-1);
	}
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
		return (errmsg_n_retval("Wrong input file format", -1));
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
	{
		free_n_nullify(&hotline);
		return (clear_maplines_close_fd_retval(map_chain, map_fd, -1));
	}
	if (extract_map(map, map_chain, map_fd, &hotline) == -1)
		return (clear_maplines_close_fd_retval(map_chain, map_fd, -1));
	return (clear_maplines_close_fd_retval(map_chain, map_fd, 0));
}


int	got_all_elems(t_mapstuff *map)
{
	if (map->NO_texture == NULL || map->SO_texture == NULL
		|| map->WE_texture == NULL || map->EA_texture == NULL
		|| !color_alr_set(map->Fcolor) || !color_alr_set(map->Ccolor))
		return (errmsg_n_retval("Not all graphics elements found", -1));
	return (1);
}
