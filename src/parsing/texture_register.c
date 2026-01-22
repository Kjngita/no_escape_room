#include "header_cub3d.h"

int	compass(t_mapstuff *map, char *line, int direction)
{
	char	**extract;
	int		check;

	check = 0;
	if (direction != NO && direction != SO && direction != WE && direction != EA)
	{
		printf("%s\n", line);
		return (errmsg_n_retval("Weird line", -1));
	}
	extract = ft_split(line, " ");
	if (!extract || !extract[0] || !extract[1])
		return (errmsg_n_retval("ft_split failed in texture", -1));
	if (extract[2])
		return (errmsg_n_retval("Pls only 1 path to texture", -1));
	if (direction == NO)
		check = register_texture_NO(map, extract[1]);
	else if (direction == SO)
		check = register_texture_SO(map, extract[1]);
	else if (direction == WE)
		check = register_texture_WE(map, extract[1]);
	else if (direction == EA)
		check = register_texture_EA(map, extract[1]);
	extract = clear_2x_char_pointers(extract);
	return (check);
}

int	register_texture_NO(t_mapstuff *map, char *path)
{
	if (map->NOtexture)
		return (errmsg_n_retval("Duplicate texture NO", -1));
	map->NOtexture = ft_strdup(path);
	if (!map->NOtexture)
		return (errmsg_n_retval("strdup failed NOtexture", -1));
	return (0);
}

int	register_texture_SO(t_mapstuff *map, char *path)
{
	if (map->SOtexture)
		return (errmsg_n_retval("Duplicate texture SO", -1));
	map->SOtexture = ft_strdup(path);
	if (!map->SOtexture)
		return (errmsg_n_retval("strdup failed SOtexture", -1));
	return (0);
}

int	register_texture_WE(t_mapstuff *map, char *path)
{
	if (map->WEtexture)
		return (errmsg_n_retval("Duplicate texture WE", -1));
	map->WEtexture = ft_strdup(path);
	if (!map->WEtexture)
		return (errmsg_n_retval("strdup failed WEtexture", -1));
	return (0);
}

int	register_texture_EA(t_mapstuff *map, char *path)
{
	if (map->EAtexture)
		return (errmsg_n_retval("Duplicate texture EA", -1));
	map->EAtexture = ft_strdup(path);
	if (!map->EAtexture)
		return (errmsg_n_retval("strdup failed EAtexture", -1));
	return (0);
}
