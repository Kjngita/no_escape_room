#include "header_cub3d.h"

uint32_t	bitshift_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	paintbrush(t_mapstuff *map, char *line, int surface)
{
	if (color_line_check(line) == -1)
		return (-1);
	if (surface == F)
	{
		if (floor_color(map, line) == -1)
			return (-1);
	}
	else if (surface == C)
	{
		if (ceiling_color(map, line) == -1)
			return (-1);
	}
	if (color_alr_set(map->Fcolor) && color_alr_set(map->Ccolor))
	{
		if (map->Fcolor == map->Ccolor)
			return (errmsg_n_retval("Same color for floor & ceiling", -1));
	}
	return (0);
}

int	color_line_check(char *line)
{
	size_t	i;
	size_t	comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (ft_strchr("FC, ", line[i]) == NULL && !ft_isdigit(line[i]))
		{
			printf("\n%c\n", line[i]);
			return (errmsg_n_retval("Color line: Foreign character", -1));
		}
		if (line[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return (errmsg_n_retval("Comma coma", -1));
	return (0);
}

/*
Extract the alpha channel of a color. Alpha's value is the last 8 bit stored
in the color which was initialized as 0 in the beginning. Masking with 0xFF to
check if it was changed to 255, meaning the color was registered.

Return: 0 for not yet register color, 1 for already done
*/
int	color_alr_set(uint32_t color)
{
	uint8_t	a_value;

	a_value = color & 0xFF; printf("Color %u alpha %u\n", color, a_value);
	if (a_value == 0)
		return (0);
	return (1);
}

int	floor_color(t_mapstuff *map, char *line)
{
	char	**splitted;
	int		r;
	int		g;
	int		b;

	if (color_alr_set(map->Fcolor))
		return (errmsg_n_retval("Duplicate floor color", -1));
	splitted = ft_split(line, " ,");
	if (!splitted)
		return (errmsg_n_retval("ft_split failed Fcolor", -1));
	if (!splitted[1] || !splitted[2] || !splitted[3] || splitted[4] != NULL)
		return (errmsg_n_retval("Smt fishy ft_split Fcolor", -1));
	r = cub3d_atoi(splitted[1]);
	g = cub3d_atoi(splitted[2]);
	b = cub3d_atoi(splitted[3]);
	splitted = clear_2x_char_pointers(splitted);
	if (r < 0 || g < 0 || b < 0)
		return (errmsg_n_retval("Invalid input for floor color", -1));
	map->Fcolor = bitshift_rgba((uint8_t)r, (uint8_t)g, (uint8_t)b, 255); printf("~~Changed F color~~\n");
	return (0);	
}

int	ceiling_color(t_mapstuff *map, char *line)
{
	char	**splitted;
	int		r;
	int		g;
	int		b;

	if (color_alr_set(map->Ccolor))
		return (errmsg_n_retval("Duplicate ceiling color", -1));
	splitted = ft_split(line, " ,");
	if (!splitted)
		return (errmsg_n_retval("ft_split failed Ccolor", -1));
	if (!splitted[1] || !splitted[2] || !splitted[3] || splitted[4] != NULL)
		return (errmsg_n_retval("Smt fishy ft_split Ccolor", -1));
	r = cub3d_atoi(splitted[1]);
	g = cub3d_atoi(splitted[2]);
	b = cub3d_atoi(splitted[3]);
	splitted = clear_2x_char_pointers(splitted);
	if (r < 0 || g < 0 || b < 0)
		return (errmsg_n_retval("Invalid input for ceiling color", -1));
	map->Ccolor = bitshift_rgba((uint8_t)r, (uint8_t)g, (uint8_t)b, 255); printf("~~Changed C color~~\n");
	return (0);	
}

/*
Turn a string to integer.
Other than 1 possible sign for the number, accept only digits.

Return: -1 on errors (not standard/not in 0-255 range integer) 
or the converted integer
*/
int	cub3d_atoi(char *str)
{
	size_t		i;
	uint32_t	nbr;

	if (!str)
		return (-1);
	i = 0;
	nbr = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i])
	{
		if (nbr > 255 || str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = (nbr * 10 + str[i]) - '0';
		i++;
	}
	if (str[i] != 0)
		return (-1);
	return (nbr);
}
