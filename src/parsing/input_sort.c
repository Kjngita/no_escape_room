#include "header_cub3d.h"

int	extract_graphics_elements(t_mapstuff *map, int map_fd, char **hotline)
{
	char	*line;
	int		eof;
	int		check;

	eof = 0;
	while (1)
	{
		line = get_next_line(map_fd, &eof);
		if (!line)
		{
			if (eof == 1)
				break ;
			return (errmsg_n_retval("Could not read map line", -1));
		}
		line[strlen_no_nl(line)] = '\0';
		check = what_kinda_line(map, &line, hotline);
		if (check == -1)
			return (-1);
		else if (check == 1)
			return (got_all_elems(map));
		free (line);
	}
	return (got_all_elems(map));
}

int	what_kinda_line(t_mapstuff *map, char **line, char **hotline)
{
	if (line_is_empty(*line))
		return (0);
	else if (line_is_start_of_map(*line))
	{
		*hotline = ft_strdup(*line);
		free_n_nullify(line);
		if (!*hotline)
			return (errmsg_n_retval("strdup 1st map line failed", -1));
		return (1);
	}
	else if (line_has_info(map, *line) == -1)
	{
		free_n_nullify(line);
		return (-1);
	}
	return (0);
}

int	line_is_empty(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	line_is_start_of_map(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(" 1", line[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

int	line_has_info(t_mapstuff *map, char *line)
{
	char	**broken_down_line;
	int		info;
	size_t	i;

	i = 0;
	while (line[i++])
	{
		if (line[i] == '\t' || line[i] == '\v' || line[i] == '\f'
			|| line[i] == '\r')
			return (errmsg_n_retval("Found unsupported whitespace", -1));
	}
	broken_down_line = ft_split(line, " ");
	if (!broken_down_line || !broken_down_line[0])
		return (errmsg_n_retval("ft_split failed line info", -1));
	info = categorize(broken_down_line[0]);
	broken_down_line = clear_2x_char_pointers(broken_down_line);
	if (info == ALIEN)
		return (errmsg_n_retval("Wrong identifier", -1));
	if (info == F || info == C)
		return (paintbrush(map, line, info));
	else
		return (compass(map, line, info));
}


