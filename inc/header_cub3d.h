#ifndef HEADER_CUB3D_H
# define HEADER_CUB3D_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>


#define WIDTH 1920 // Default starting screen width
#define HEIGHT 1080 // Default starting screen height
#define MOVE_SPEED 0.06 // Move amount per frame
#define ROT_SPEED 0.02 // Turn amount per frame
#define TILE_SIZE 64  // Used by minimap test build
#define	HUGE_DELTA 1e30 // Functionally infinite delta, when dir_x or dir_y == 0

//	Wall colors used for solid color rendering
#define W_COLOR 0xFBF8CCFF
#define E_COLOR 0xCFBAF0FF
#define N_COLOR 0xFDE4CFFF
#define S_COLOR 0xF1C0E8FF
#define COLOR_MISSING 0xFE019AFF

enum	e_categorization
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

typedef struct s_maplines
{
	char				*mapline;
	struct s_maplines	*next;
}	t_maplines;

typedef struct s_map
{
	mlx_texture_t	*NO_texture;
	mlx_texture_t	*SO_texture;
	mlx_texture_t	*WE_texture;
	mlx_texture_t	*EA_texture;
	uint32_t		Fcolor;
	uint32_t		Ccolor;
	char			start_pos; //Player start facing 
	size_t			player_start_x;
	size_t			player_start_y;
	char			**dungeon;
}	t_mapstuff;

typedef struct s_data
{
	// ------------ MLX data
	mlx_t			*window; // the "frame" where canvas is placed
	mlx_image_t 	*img; // the "canvas" where pixels are drawn
	// ------------ Player state 
	double			pos_x; //exact player position, ex. 5.5
	double			pos_y; //exact player position, ex. 5.5
	double			dir_x; //x offset of point player is facing (x + y sum remains constant when rotating view)
	double			dir_y; //y offet of point player is facing (x + y sum remains constant when rotating view)
	double			plane_x; //x offset of right edge of view plane, from dir_x
	double			plane_y; //y offset of right edge of view plane, from dir_y
	// ------------ Parsed data
	t_mapstuff		map_data;
}	t_data;

//used to explitly track which wall face a ray hits
typedef enum e_face
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
}	t_face;

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

int			parse_input(t_mapstuff *map, int ac, char **av);
void		free_n_nullify(char **useless);
void		*clear_2x_char_pointers(char **trash);
void		clear_maplines(t_maplines *map_chain);
void		wipe_map(t_mapstuff *map);
int			errmsg_n_retval(char *msg, int value);

int			check_map_extension(char *map_name);
int			strlen_no_nl(char *line);
int			map_content(t_mapstuff *map, char *map_name);
int			extract_graphics_elements(t_mapstuff *map, int map_fd, char **hotline);
int			what_kinda_line(t_mapstuff *map, char **line, char **hotline);

int			line_has_info(t_mapstuff *map, char *line);
int			categorize(char *text);
int			compass(t_mapstuff *map, char *line, int direction);
int			file_is_png(char *path);
int			register_texture(mlx_texture_t **wall_texture, char *path);

int			line_is_empty(char *line);
int			line_is_start_of_map(char *line);
int			got_all_elems(t_mapstuff *map);

uint32_t	bitshift_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int			paintbrush(t_mapstuff *map, char *line, int surface);
int			color_line_check(char *line);
int			color_alr_set(uint32_t color);
int			cub3d_atoi(char *str);
int			set_color(uint32_t *surface_color, char *line);

int			extract_map(t_mapstuff *map, t_maplines *map_chain, int map_fd,
			char **map_1stline);
int			map_line_acceptable(t_mapstuff *map, t_maplines *map_chain, char *line, size_t line_no);
int			start_pos_setup(t_mapstuff *map, char direction, size_t x_coord,
			size_t y_coord);
int			add_to_flatmap(t_maplines *map_chain, char **line_to_add, size_t line_no);
int			map_valid(t_mapstuff *map, t_maplines *map_chain, size_t map_height);
int			copy_linkedlist_to_2xpointers(t_maplines *map_chain, char **dest);
void		flood_fill(char **testmap, size_t x_coord, size_t y_coord, int *hole);

void	draw_ray(t_data *data, t_ray *ray, mlx_image_t *img);
void	cast_rays(t_data *data);
void	init_ray(t_data *data, t_ray *ray, int x);

void	fill_background(t_data *data);
void	calc_line_height(t_data *data, t_ray *ray);
void	find_wall_x(t_data *data, t_ray *ray);
void	draw_wall_line(t_data *data, t_ray *ray);

void	init_player_start(t_data *data);
void	init_map(t_data *data);
void	init_colors(t_data *data);

void	draw_map(t_data *data);

void	rotate(t_data *data, int dir);
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);

#endif