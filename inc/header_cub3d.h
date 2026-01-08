#ifndef HEADER_CUB3D_H
# define HEADER_CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_map
{
	char	*NOtexture;
	char	*SOtexture;
	char	*WEtexture;
	char	*EAtexture;
	int		Fcolor;
	int		Ccolor;
	char	**flatmap;
	
}	t_mapstuff;


int	errmsg_n_retval(char *msg, int value);
int	check_map_extension(char *map_name);
int	map_content(t_mapstuff *map, char *map_name);
int	extract_graphics_elements(t_mapstuff *map, int map_fd);

#endif