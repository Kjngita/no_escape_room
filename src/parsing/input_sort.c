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
	return (0);
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

	broken_down_line = ft_split(line, " ");
	if (!broken_down_line || !broken_down_line[0])
		return (errmsg_n_retval("ft_split failed line info", -1));
	info = categorize(broken_down_line[0]); //printf("direction = %i\n", info);
	broken_down_line = clear_2x_char_pointers(broken_down_line);
	if (info == F || info == C)
		return (paintbrush(map, line, info));
	else
		return (compass(map, line, info));
}

int	categorize(char *text)
{ //printf("Categorize %s\n", text);
	if (ft_strncmp(text, "NO", 3) == 0)
		return (NO);
	else if (ft_strncmp(text, "SO", 3) == 0)
		return (SO);
	else if (ft_strncmp(text, "WE", 3) == 0)
		return (WE);
	else if (ft_strncmp(text, "EA", 3) == 0)
		return (EA);
	else if (ft_strncmp(text, "F", 2) == 0)
		return (F);
	else if (ft_strncmp(text, "C", 2) == 0)
		return (C);
	else
		return (-123);
}

