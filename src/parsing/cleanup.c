/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:48:10 by gita              #+#    #+#             */
/*   Updated: 2026/02/09 21:48:11 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
Delete the textures and free the map double pointer that were loaded into the
`t_mapstuff` struct
*/
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

/*
Free a char pointer and assign it as NULL to prevent dangling pointer
*/
void	free_n_nullify(char **useless)
{
	if (*useless)
	{
		free (*useless);
		*useless = NULL;
	}
}

/*
Free each of the strings in the double pointer then free the double pointer
itself

Return: NULL (nullify the double pointer)
*/
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

/*
- If there is a linked list of `t_maplines` struct, for each node perform
freeing and nulifying the string, free the pointer to the node then make it
move along the list until it becomes a NULL pointer
- If there is any fd open, close it

Return: the value passed to the function, either -1 for errors or 0 for normal
*/
int	clear_maplines_close_fd_retval(t_maplines *map_chain, int fd, int value)
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
	if (fd > 0)
		close(fd);
	return (value);
}

/*
Print the error message and end the string passed to the function with a `\n`

Return: the value passed to the function, mostly -1 for errors
*/
int	errmsg_n_retval(char *msg, int value)
{
	if (msg)
	{
		printf("Error\n");
		printf("%s\n", msg);
	}
	return (value);
}
