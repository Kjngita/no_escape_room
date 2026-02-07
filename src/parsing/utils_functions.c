#include "header_cub3d.h"

/*
Return: length of a string, disregarding the possible \n at the end
*/
int	strlen_no_nl(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

/*
Check if a line is empty or contains only spaces (also considered empty).

Return: 1 if line is empty, 0 if not
*/
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

/*
Extract the alpha channel of a color. Alpha's value is the last 8 bit stored
in the color which was initialized as 0 in the beginning. Masking with 0xFF to
check if it was changed to 255, meaning the color was registered.

Return: 0 for not yet register color, 1 for already done
*/
int	color_alr_set(uint32_t color)
{
	uint8_t	a_value;

	a_value = color & 0xFF;
	if (a_value == 0)
		return (0);
	return (1);
}
