#ifndef HEADER_CUB3D_H
# define HEADER_CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_maplines
{
	char				*mapline;
	struct s_maplines	*next;
}	t_maplines;


typedef struct s_map
{
	char		*NOtexture;
	char		*SOtexture;
	char		*WEtexture;
	char		*EAtexture;
	uint32_t	Fcolor;
	uint32_t	Ccolor;
	char		orientation;
	t_maplines	*flatmap;
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


void		free_n_nullify(char **useless);
void		*clear_2x_char_pointers(char **trash);
void		wipe_map(t_mapstuff *map);
int			errmsg_n_retval(char *msg, int value);

int			check_map_extension(char *map_name);
int			strlen_no_nl(char *line);
int			map_content(t_mapstuff *map, char *map_name);
int			extract_graphics_elements(t_mapstuff *map, int map_fd, char **hotline);
int			what_kinda_line(t_mapstuff *map, int map_fd, char *line, char **hotline);

int			line_has_info(t_mapstuff *map, char *line);
int			categorize(char *text);
int			compass(t_mapstuff *map, char *line, int direction);
int			register_texture_NO(t_mapstuff *map, char *line);
int			register_texture_SO(t_mapstuff *map, char *line);
int			register_texture_WE(t_mapstuff *map, char *line);
int			register_texture_EA(t_mapstuff *map, char *line);

int			line_is_empty(char *line);
int			line_is_start_of_map(char *line);
int			got_all_elems(t_mapstuff *map);

uint32_t	bitshift_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int			paintbrush(t_mapstuff *map, char *line, int surface);
int			color_line_check(char *line);
int			color_alr_set(uint32_t color);
int			cub3d_atoi(char *str);
int			floor_color(t_mapstuff *map, char *line);
int			ceiling_color(t_mapstuff *map, char *line);

#endif