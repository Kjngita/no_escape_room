#include "header_cub3d.h"

int	compass(t_mapstuff *map, char *line, int direction)
{
	if (direction == NO)
		return (register_texture_NO(map, line));
	else if (direction == SO)
		return (register_texture_SO(map, line));
	else if (direction == WE)
		return (register_texture_WE(map, line));
	else if (direction == EA)
		return (register_texture_EA(map, line));
	else
	{
		printf("Line %s\n", line);
		return (errmsg_n_retval("Weird line", -1));
	}
}

int	register_texture_NO(t_mapstuff *map, char *line)
{
	if (map->NOtexture)
		return (errmsg_n_retval("Duplicate texture NO", -1));
	map->NOtexture = ft_strdup(line);
	if (!map->NOtexture)
		return (errmsg_n_retval("strdup failed NOtexture", -1));
	return (0);
}

int	register_texture_SO(t_mapstuff *map, char *line)
{
	if (map->SOtexture)
		return (errmsg_n_retval("Duplicate texture SO", -1));
	map->SOtexture = ft_strdup(line);
	if (!map->SOtexture)
		return (errmsg_n_retval("strdup failed SOtexture", -1));
	return (0);
}

int	register_texture_WE(t_mapstuff *map, char *line)
{
	if (map->WEtexture)
		return (errmsg_n_retval("Duplicate texture WE", -1));
	map->WEtexture = ft_strdup(line);
	if (!map->WEtexture)
		return (errmsg_n_retval("strdup failed WEtexture", -1));
	return (0);
}

int	register_texture_EA(t_mapstuff *map, char *line)
{
	if (map->EAtexture)
		return (errmsg_n_retval("Duplicate texture EA", -1));
	map->EAtexture = ft_strdup(line);
	if (!map->EAtexture)
		return (errmsg_n_retval("strdup failed EAtexture", -1));
	return (0);
}
