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

enum	e_categorization
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

int	errmsg_n_retval(char *msg, int value);
int	check_map_extension(char *map_name);
int	strlen_no_nl(char *line);
int	map_content(t_mapstuff *map, char *map_name);
int	extract_graphics_elements(t_mapstuff *map, int map_fd);

int	line_has_info(t_mapstuff *map, char *line);
int	categorize(char *text);
int	compass(t_mapstuff *map, char *line, int direction);
int	register_texture_NO(t_mapstuff *map, char *line);
int	register_texture_SO(t_mapstuff *map, char *line);
int	register_texture_WE(t_mapstuff *map, char *line);
int	register_texture_EA(t_mapstuff *map, char *line);

int	line_is_empty(char *line);
int	line_is_start_of_map(char *line);
int	got_all_elems(t_mapstuff *map, char *line_startmap, int map_fd);

#endif