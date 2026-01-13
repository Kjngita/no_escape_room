#include "header_cub3d.h"

int	paintbrush(t_mapstuff *map, char *line, int surface)
{
	color_line_check(line);
	if (surface == F)
	{
		floor_color(map, line);
	}
	// else if (surface == C)
	// {

	// }

	if (F != -1 && C != -1)
	{
		if (F == C)
			return (errmsg_n_retval("Same color for floor & ceiling", -1));
	}
	return (0);
}

int	color_line_check(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("FC, ", line[i]) == NULL || !ft_isdigit(line[i]))
			return (errmsg_n_retval("Color line: Foreign character", -1));
		i++;
	}
	return (0);
}

int	floor_color(t_mapstuff *map, char *line)
{
	if (map->Fcolor != -1)
		return (errmsg_n_retval("Duplicate floor color", -1));
}
