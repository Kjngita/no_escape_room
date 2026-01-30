#include "header_cub3d.h"

int	compass(t_mapstuff *map, char *line, int direction)
{
	char	**extract;
	int		check;

	check = 0;
	if (direction != NO && direction != SO && direction != WE 
		&& direction != EA)
		return (errmsg_n_retval("Weird line", -1));
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

int	file_is_png(char *path)
{
	if (!path)
		return (errmsg_n_retval("Could not see file path", 0));
	if (ft_strcmp(path + (ft_strlen(path) - 4), ".png"))
		return (errmsg_n_retval("Wrong texture file extension", 0));
	return (1);
}

int	register_texture_NO(t_mapstuff *map, char *path)
{
	if (!file_is_png(path))
		return (-1);
	if (map->NO_texture)
		return (errmsg_n_retval("Duplicate texture NO", -1));
	map->NO_texture = mlx_load_png(path);
	if (!map->NO_texture)
		return(errmsg_n_retval("Failed to load NO png", -1));
	return (0);
}

int	register_texture_SO(t_mapstuff *map, char *path)
{
	if (!file_is_png(path))
		return (-1);
	if (map->SO_texture)
		return (errmsg_n_retval("Duplicate texture SO", -1));
	map->SO_texture = mlx_load_png(path);
	if (!map->SO_texture)
		return(errmsg_n_retval("Failed to load SO png", -1));
	return (0);
}

int	register_texture_WE(t_mapstuff *map, char *path)
{
	if (!file_is_png(path))
		return (-1);
	if (map->WE_texture)
		return (errmsg_n_retval("Duplicate texture WE", -1));
	map->WE_texture = mlx_load_png(path);
	if (!map->WE_texture)
		return(errmsg_n_retval("Failed to load WE png", -1));
	return (0);
}

int	register_texture_EA(t_mapstuff *map, char *path)
{
	if (!file_is_png(path))
		return (-1);
	if (map->EA_texture)
		return (errmsg_n_retval("Duplicate texture EA", -1));
	map->EA_texture = mlx_load_png(path);
	if (!map->EA_texture)
		return(errmsg_n_retval("Failed to load EA png", -1));
	return (0);
}
