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
	if (map->dungeon)
		map->dungeon = clear_2x_char_pointers(map->dungeon);
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

void	clear_maplines(t_maplines *map_chain)
{
	t_maplines	*del;

	while (map_chain)
	{
		del = map_chain->next;
		if (map_chain->mapline)
			free_n_nullify(&map_chain->mapline);
		free (map_chain);
		map_chain = del;
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
