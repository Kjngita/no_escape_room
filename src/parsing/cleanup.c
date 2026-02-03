#include "header_cub3d.h"

void	wipe_map(t_mapstuff *map)
{
	if (!map)
		return ;
	if (map->NO_texture)
		mlx_delete_texture(map->NO_texture);
	if (map->SO_texture)
		mlx_delete_texture(map->SO_texture);
	if (map->WE_texture)
		mlx_delete_texture(map->WE_texture);
	if (map->EA_texture)
		mlx_delete_texture(map->EA_texture);
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

int	clear_maplines_close_fd_retval(t_maplines *map_chain, int fd, int value)
{
	t_maplines	*del;

	if (map_chain != NULL)
	{
		while (map_chain)
		{
			del = map_chain->next;
			if (map_chain->mapline)
				free_n_nullify(&map_chain->mapline);
			free (map_chain);
			map_chain = del;
		}
	}
	if (fd > 0)
		close(fd);
	return (value);
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
