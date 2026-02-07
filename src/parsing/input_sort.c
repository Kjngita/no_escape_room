#include "header_cub3d.h"

/*
- Read input file line by line
- Check each line whether empty, start of map, or other cases
- If not encountering error, stop execution loop once hitting map 1st line

Return: Result from `got_all_elems()`, or -1 on errors
*/
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

/*
(helper function of `extract_graphics_elements()`)
- Check if line is an empty line
- If not, check if line is start of map. If so, ft_strdup line to the string
passed to function
- If not, check what line has

Return: 0 on normal line - can continue, -1 on errors, 1 on map 1st line
*/
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

/*
(helper function of `what_kinda_line()`)
Check if line has only `' '`s and `'1'`s, which signifies line is start of map.

Return: 1 if line is start of map, 0 if not
*/
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

/*
(helper function of `what_kinda_line()`)
- Check for other whitespace characters other than `' '` and `'\n'`
- Split the line with `' '` and pass the first argument to helper function
to see if line contains graphical element identifier
- If line has floor/ceiling color identifier, redirect to `paintbrush()`.
If line has texture identifier, redirect to `compass()`.

Return: -1 on errors, result from `paintbrush()` or `compass()`
*/
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
	if (info == UNRECOGNIZED)
		return (errmsg_n_retval("Wrong identifier", -1));
	if (info == F || info == C)
		return (paintbrush(map, line, info));
	else
		return (compass(map, line, info));
}

/*
(helper function of `line_has_info()`)
Compare the string passed to the function with graphical identifiers.

Return: the corresponding enum value when a match is found, 
or UNRECOGNIZED in other cases
*/
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
		return (UNRECOGNIZED);
}
