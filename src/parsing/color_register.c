/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_register.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:48:29 by gita              #+#    #+#             */
/*   Updated: 2026/02/09 21:48:30 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_cub3d.h"

/*
Combine 4 individual channel bytes into a single integer using bit-shifting.
8 bits representing the value of red channel is shifted 3 bytes to the left,
green - 2 bytes, blue - 1 byte, and alpha channel occupy the last byte.

Return: An uint32_t number that has (r | g | b | a) info of a color
*/
uint32_t	bitshift_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/*
(helper function of `line_has_info()`)
- Check whether the line passed to the function is correctly constructed
- Set the floor/ceiling color according to the info from the input

Return: 0 on success, -1 on errors
*/
int	paintbrush(t_mapstuff *map, char *line, int surface)
{
	if (color_line_check(line) == -1)
		return (-1);
	if (surface == F)
	{
		if (set_color(&map->Fcolor, line) == -1)
			return (-1);
	}
	else if (surface == C)
	{
		if (set_color(&map->Ccolor, line) == -1)
			return (-1);
	}
	return (0);
}

/*
(helper function of `paintbrush()`)
- Check whether there is any foreign character than those expected in a
color input line
- Check if the number of commas appearing in the line is 2

Return: 0 for acceptable line, -1 for errors
*/
int	color_line_check(char *line)
{
	size_t	i;
	size_t	comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (ft_strchr("FC, +", line[i]) == NULL && !ft_isdigit(line[i]))
			return (errmsg_n_retval("Color line: Foreign character", -1));
		if (line[i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		return (errmsg_n_retval("Color comma coma", -1));
	return (0);
}

/*
(helper function of `paintbrush()`)
- Check if the color was set previously
- Check if the color values are within range

Return: 0 on success, -1 on errors
*/
int	set_color(uint32_t *surface_color, char *line)
{
	char	**splitted;
	int		r;
	int		g;
	int		b;

	if (color_alr_set(*surface_color))
		return (errmsg_n_retval("Duplicate color registration", -1));
	splitted = ft_split(line, " ,");
	if (!splitted)
		return (errmsg_n_retval("ft_split failed setting color", -1));
	if (!splitted[1] || !splitted[2] || !splitted[3] || splitted[4] != NULL)
	{
		splitted = clear_2x_char_pointers(splitted);
		return (errmsg_n_retval("Smt fishy ft_split setting color", -1));
	}
	r = cub3d_atoi(splitted[1]);
	g = cub3d_atoi(splitted[2]);
	b = cub3d_atoi(splitted[3]);
	splitted = clear_2x_char_pointers(splitted);
	if (r < 0 || g < 0 || b < 0)
		return (errmsg_n_retval("Invalid input for color", -1));
	*surface_color = bitshift_rgba((uint8_t)r, (uint8_t)g, (uint8_t)b, 255);
	return (0);
}

/*
(helper function of `set_color()`)
Turn a string to integer.
Other than 1 positive sign at the front of the string, accept only digits.

Return: -1 on errors (not standard/not in 0-255 range integer) 
or the converted integer
*/
int	cub3d_atoi(char *str)
{
	size_t		i;
	int			nbr;

	if (!str)
		return (-1);
	i = 0;
	nbr = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = (nbr * 10 + str[i]) - '0';
		i++;
	}
	if (nbr > 255)
		return (-1);
	return (nbr);
}
