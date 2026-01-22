#include "header_cub3d.h"

void	wipe_map(t_mapstuff *map)
{
	if (!map)
		return ;
	if (map->NOtexture)
		free_n_nullify(&map->NOtexture);
	if (map->SOtexture)
		free_n_nullify(&map->SOtexture);
	if (map->WEtexture)
		free_n_nullify(&map->WEtexture);
	if (map->EAtexture)
		free_n_nullify(&map->EAtexture);
	if (map->flatmap)
		clear_maplines(map);
}

void	free_n_nullify(char **useless)
{
	if (*useless)
	{
		free (*useless);
		*useless = NULL;
	}
}

void	*clear_2x_char_pointers(char **trash)
{
	size_t	i;

	if (!trash)
		return (NULL);
	i = 0;
	while (trash[i] != NULL)
	{
		free_n_nullify(&trash[i]);
		i++;
	}
	if (trash)
		free (trash);
	return (NULL);
}

void	clear_maplines(t_mapstuff *map)
{
	t_maplines	*del;

	while (map->flatmap)
	{
		del = map->flatmap->next;
		if (map->flatmap->mapline)
			free_n_nullify(&map->flatmap->mapline);
		free (map->flatmap);
		map->flatmap = del;
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
