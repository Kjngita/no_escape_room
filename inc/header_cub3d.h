#ifndef HEADER_CUB3D_H
# define HEADER_CUB3D_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

#define WIDTH 1920
#define HEIGHT 1080
#define MOVE_SPEED 0.06
#define ROT_SPEED 0.02
#define SCALE 100
#define TILE_SIZE 64  // Pixels per map square
#define LINE_LEN 50   // How long the red line looks
#define MAP_HEIGHT 10
#define MAP_WIDTH 10
#define	RAY_COUNT 1000
#define	HUGE_DELTA 1e30
#define C_COLOR 0x90DBF4FF
#define F_COLOR 0xB9FBC0FF
#define W_COLOR 0xFBF8CCFF
#define E_COLOR 0xCFBAF0FF
#define N_COLOR 0xFDE4CFFF
#define S_COLOR 0xF1C0E8FF
#define COLOR_MISSING 0xFE019AFF

typedef enum e_face
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_face;

typedef struct s_data
{
	mlx_t			*window;
	mlx_image_t 	*img;
	double			pos_x; //exact player position, ex. 5.5
	double			pos_y; //exact player position, ex. 5.5
	double			dir_x; //x offset of point player is facing (x + y sum constant)
	double			dir_y; //y offet of point player is facing (x + y sum constant)
	double			plane_x; //x offset of right edge of view plane, from dir_x
	double			plane_y; //y offset of right edge of view plane, from dir_y
	int				map[10][10];
}	t_data;

/*

*/

//used by cast_rays to store variables
typedef struct s_ray
{
	// RAY DIRECTION
	double	camera_x; // ray position along camera plane, between -1 and 1
	double	ray_dir_x; //if camera_x = 0, equal to dir_x
	double	ray_dir_y; //if camera_x = 0, equal to dir_y

	// WALL DETECTION & DISTANCE CALCULATION
	int		map_x; //current map square
	int		map_y; //current map square
	double	step_x; //direction to advance ray: -1 (left) or 1 (right)
	double	step_y; //direction to advance ray: -1 (up) or 1 (down)
	double	delta_x; //delta x: diagonal distance to travel between VERTICAL grid lines
	double	delta_y; //delta y: diagonal distance to travel between HORIZONTAL grid lines
	double	side_dist_x; //distance to next x grid line from origin (increments by delta_x)
	double	side_dist_y; //distance to next y grid line from origin (increment by delta_y)
	double	wall_dist; //diagonal distance from player to wall
	int		side; // 0: vertical (N TO S) wall hit, 1 if horizontal (W to E)
	t_face	wall_face; //which wall face the ray hit

	// RENDERING
	double	wall_x; //exact hit location on wall, range 0.0 - 1.0
	int	texture_x; //pixel column that wall_x corresponds to, range 0 - texture width
	int	screen_x; //screen pixel column to draw
	int	line_height; //how high to draw the wall column
	int	line_top; //screen y pixel to start drawing from
	int	line_bottom; //screen y pixel to stop drawing at

}	t_ray;

//used by draw_line to store variables
typedef struct s_line
{
	int	dx; //delta x: total horizontal distance from start to end
	int	dy; //delta y: total vertical distance from start to end
	int	sx; //step x: horizontal direction, either 1 (right) or -1 (left)
	int	sy; //step y: vertical direction, either 1 (up) or -1 (down)
	int	err; //tracks drift from perfect mathematical line
	int	e2; //err * 2 for calculation efficiency
	int		map_x;
	int		map_y;
}	t_line;

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

void	free_n_nullify(char **useless);
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
int	got_all_elems(t_mapstuff *map, int map_fd);

void	draw_ray(t_data *data, t_ray *ray, mlx_image_t *img);
void	cast_rays(t_data *data);
void	init_ray(t_data *data, t_ray *ray, int x);

void	fill_background(t_data *data);
void	calc_line_height(t_ray *ray);
void	draw_wall_line(t_data *data, t_ray *ray);

void	init_facing(t_data *data, unsigned char facing);
void	init_map(t_data *data);
void	init_colors(t_data *data);

void	draw_map(t_data *data);

void	rotate(t_data *data, int dir);
void	move_forward(t_data *data);
void	move_backward(t_data *data);

#endif