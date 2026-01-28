#include "header_cub3d.h"

int	compass(t_data *data, char *line, int direction)
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
		check = register_texture_NO(data, extract[1]);
	else if (direction == SO)
		check = register_texture_SO(data, extract[1]);
	else if (direction == WE)
		check = register_texture_WE(data, extract[1]);
	else if (direction == EA)
		check = register_texture_EA(data, extract[1]);
	extract = clear_2x_char_pointers(extract);
	return (check);
}

int	register_texture_NO(t_data *data, char *path)
{
	if (data->map->texture_set[0] == 1)
	return (errmsg_n_retval("Duplicate texture NO", -1));
	else
	{
		data->map->texture_set[0] = 1;
		data->map->NO_img = load_texture(data, path);
		if (!data->map->NO_img)
		return(-1);
	}
	return (0);
}

int	register_texture_SO(t_data *data, char *path)
{
	if (data->map->texture_set[1] == 1)
	return (errmsg_n_retval("Duplicate texture SO", -1));
	else
	{
		data->map->texture_set[1] = 1;
		data->map->SO_img = load_texture(data, path);
		if (!data->map->SO_img)
			return(-1);
		}
	return (0);
}

int	register_texture_WE(t_data *data, char *path)
{
	if (data->map->texture_set[2] == 1)
	return (errmsg_n_retval("Duplicate texture WE", -1));
	else
	{
		data->map->texture_set[2] = 1;
		data->map->WE_img = load_texture(data, path);
		if (!data->map->WE_img)
		return(-1);
	}
	return (0);
}

int	register_texture_EA(t_data *data, char *path)
{
	if (data->map->texture_set[3] == 1)
	return (errmsg_n_retval("Duplicate texture EA", -1));
	else
	{
		data->map->texture_set[3] = 1;
		data->map->EA_img = load_texture(data, path);
		if (!data->map->EA_img)
		return(-1);
	}
	return (0);
}

mlx_image_t	*load_texture(t_data *data, char *path)
{
	mlx_texture_t	*vessel;
	mlx_image_t		*package;

	vessel = mlx_load_png(path);
	if (!vessel)
	{
		errmsg_n_retval("Could not load png", -1);
		return (NULL);
	}
	package = mlx_texture_to_image(data->window, vessel);
	if (!package)
	{
		mlx_delete_texture(vessel);
		errmsg_n_retval("Could not load img", -1);
		return (NULL);
	}
	mlx_delete_texture(vessel);
	return (package);
}
