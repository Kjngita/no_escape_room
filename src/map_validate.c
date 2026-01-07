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
	if (ac < 2)
		return (errmsg_n_retval("No map provided", 1));
	if (ac > 2)
		return (errmsg_n_retval("Only 1 map at a time pls", 1));
	if (check_map_extension(av[1]) == -1)
		return (1);
	if (map_content(av[1]) == -1)
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

int	map_content(char *map_name)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (errmsg_n_retval("Cannot open map file", -1));
	return (0);
}