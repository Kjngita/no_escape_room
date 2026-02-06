#include "header_cub3d.h"

int	compass(t_mapstuff *map, char *line, int direction)
{
	char	**extract;
	int		check;

	check = 0;
	extract = ft_split(line, " ");
	if (!extract || !extract[0] || !extract[1])
		return (errmsg_n_retval("ft_split failed in texture", -1));
	if (extract[2])
		return (errmsg_n_retval("Pls only 1 path to texture", -1));
	if (direction == NO)
		check = register_texture(&map->NO_texture, extract[1]);
	else if (direction == SO)
		check = register_texture(&map->SO_texture, extract[1]);
	else if (direction == WE)
		check = register_texture(&map->WE_texture, extract[1]);
	else if (direction == EA)
		check = register_texture(&map->EA_texture, extract[1]);
	extract = clear_2x_char_pointers(extract);
	return (check);
}

int	register_texture(mlx_texture_t **wall_texture, char *path)
{
	if (*wall_texture)
		return (errmsg_n_retval("Duplicate texture registration", -1));
	if (!file_is_png(path))
		return (-1);
	*wall_texture = mlx_load_png(path);
	if (!*wall_texture)
		return(errmsg_n_retval("Failed to load png", -1));
	return (0);
}

int	file_is_png(char *path)
{
	if (!path)
		return (errmsg_n_retval("Could not see file path", 0));
	if (ft_strlen(path) < 4)
		return (errmsg_n_retval("Texture file name too short", 0));
	if (ft_strcmp(path + (ft_strlen(path) - 4), ".png"))
		return (errmsg_n_retval("Wrong texture file extension", 0));
	return (1);
}
