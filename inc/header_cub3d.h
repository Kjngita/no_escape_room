#ifndef HEADER_CUB3D_H
# define HEADER_CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_map
{
	char	**flatmap;
	
}	t_mapstuff;


int	errmsg_n_retval(char *msg, int value);
int	check_map_extension(char *map_name);
int	map_content(char *map_name);

#endif