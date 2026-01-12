#include "header_cub3d.h"

int	extract_graphics_elements(t_mapstuff *map, int map_fd)
{
	char	*line;
	int		eof;

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
		if (line_is_empty(line))
		{
			free_n_nullify(&line);
			continue ;
		}
		else if (line_is_start_of_map(line))
		{
			free_n_nullify(&line);
			return (got_all_elems(map, map_fd));
		}
		else if (line_has_info(map, line) == -1) //can't be first since strtrim
		{
			free_n_nullify(&line);
			return (-1);
		}
		free (line);
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
	size_t	i;
	char	**broken_down_line;
	int		direction;

	broken_down_line = ft_split(line, ' ');
	if (!broken_down_line || !broken_down_line[0])
		return (errmsg_n_retval("ft_split failed", -1));
	direction = categorize(broken_down_line[0]);
	i = 0;
	while (broken_down_line[i] != NULL)
	{
		free_n_nullify(&broken_down_line[i]);
		i++;
	}
	free_n_nullify(broken_down_line);
	if (direction == F || direction == C)
		return (100);//(paintbrush(map, line, direction));
	else
		return (compass(map, line, direction));
}
	
int	categorize(char *text)
{
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
