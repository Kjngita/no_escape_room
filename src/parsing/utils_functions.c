#include "header_cub3d.h"

int	strlen_no_nl(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
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
	int			nbr;

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
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = (nbr * 10 + str[i]) - '0';
		i++;
	}
	if (nbr > 255 || str[i] != 0)
		return (-1);
	return (nbr);
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
		return (ALIEN);
}
