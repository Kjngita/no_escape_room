/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_cub3d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjahkola <jjahkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:19:47 by jjahkola          #+#    #+#             */
/*   Updated: 2026/02/13 14:23:17 by jjahkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_CUB3D_H
# define HEADER_CUB3D_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

// Default start screen pixel width
# define WIDTH 1920
// Default start screen pixel height
# define HEIGHT 1080
// Move amount per frame
# define MOVE_SPEED 0.06
// Turn amount per frame
# define ROT_SPEED 0.02
// Used by mouse_look to dampen rotation factor
# define MOUSE_SENSITIVITY 0.08
// Functionally infinite delta, when dir_x or dir_y == 0
# define HUGE_DELTA 1e30
// Size of minimap bounding box
# define MINIMAP_SIDE 400
// Pixel width of default weapon texture
# define WEAP_W 460
// Pixel height of default weapon texture
# define WEAP_H 230

/*
NOTE: last two digits of a hexadecimal color code are the alpha channel
100 % opacity = FF (255)
50 % opacity = 80 or 7F (128)
0 % opacity = 00 (0)
*/

enum	e_categorization
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	UNRECOGNIZED
};

typedef struct s_maplines
{
	char				*mapline;
	struct s_maplines	*next;
}	t_maplines;

typedef struct s_map
{
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	// Player start facing
	char			start_pos;
	size_t			player_start_x;
	size_t			player_start_y;
	char			**dungeon;
	// Length of longest map row
	int				map_width;
	// Number of map rows
	int				map_height;
	// calculated as MINIMAP_SIZE / map_width OR map_height
	double			minimap_tile_size;
}	t_mapstuff;

typedef struct s_data
{
	// the "frame" where images are placed
	mlx_t			*window;
	// the 3d rendering is drawn here
	mlx_image_t		*img;
	// the minimap is drawn here
	mlx_image_t		*minimap;
	// the currently displayed weapon image
	mlx_texture_t	*weapon_texture;
	// the currently displayed weapon image
	mlx_image_t		*weapon;
	// flag to enable mouse look and show cursor
	int				cursor_enabled;
	// exact player x position, ex. 5.5
	double			pos_x;
	// exact player y position, ex. 5.5
	double			pos_y;
	// x offset of point player is facing, from pos_x
	double			dir_x;
	// y offet of point player is facing, from pos_y
	double			dir_y;
	// offset of right edge of view plane, from dir_x
	double			plane_x;
	// y offset of right edge of view plane, from dir_y
	double			plane_y;
	// struct containing parsed map data
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

// Used by cast_rays to store variables
typedef struct s_ray
{
	// Ray position along camera plane, between -1 and 1
	double	camera_x;
	// If camera_x = 0, equal to dir_x
	double	ray_dir_x;
	// If camera_x = 0, equal to dir_y
	double	ray_dir_y;
	// Current map square
	int		map_x;
	// Current map square
	int		map_y;
	// Direction to advance ray: -1 (left) or 1 (right)
	double	step_x;
	// Direction to advance ray: -1 (up) or 1 (down)
	double	step_y;
	// Delta x: diagonal distance to travel between VERTICAL grid lines
	double	delta_x;
	// Delta y: diagonal distance to travel between HORIZONTAL grid lines
	double	delta_y;
	// Distance to next x grid line from origin (increments by delta_x)
	double	side_dist_x;
	// Distance to next y grid line from origin (increment by delta_y)
	double	side_dist_y;
	// Diagonal distance from player to wall
	double	wall_dist;
	// 0: vertical (N TO S) wall hit, 1 if horizontal (W to E)
	int		side;
	// Which wall face the ray hit
	t_face	wall_face;
	// Exact hit location on wall, range 0.0 - 1.0
	double	wall_x;
	// Pixel column that wall_x corresponds to, range 0 - texture width
	int		texture_x;
	// Screen pixel column to draw
	int		screen_x;
	// How high to draw the wall column
	int		line_height;
	// Screen y pixel to start drawing from
	int		line_top;
	// Screen y pixel to stop drawing at
	int		line_bottom;
}	t_ray;

int			parse_input(t_mapstuff *map, int ac, char **av);
void		free_n_nullify(char **useless);
void		*clear_2x_char_pointers(char **trash);
int			clear_maplines_close_fd_retval(t_maplines *map_chain, int fd,
				int value);
void		wipe_map(t_mapstuff *map);
int			errmsg_n_retval(char *msg, int value);

int			check_map_extension(char *map_name);
int			strlen_no_nl(char *line);
int			map_content(t_mapstuff *map, char *map_name);
int			extract_graphics_elements(t_mapstuff *map, int map_fd,
				char **hotline);
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
int			build_map_loop(t_mapstuff *map, t_maplines *map_chain, int map_fd,
				size_t *line_no);
int			map_line_acceptable(t_mapstuff *map, t_maplines *map_chain,
				char *line, size_t line_no);
int			start_pos_setup(t_mapstuff *map, char direction, size_t x_coord,
				size_t y_coord);
int			add_to_flatmap(t_maplines *map_chain, char **line_to_add,
				size_t line_no);
int			map_valid(t_mapstuff *map, t_maplines *map_chain,
				size_t map_height);
int			copy_linkedlist_to_2xpointers(t_maplines *map_chain, char **dest);
int			flood_fill(char **testmap, size_t x_coord, size_t y_coord,
				size_t map_height);
int			will_fall_to_void(char **testmap, size_t x, size_t y);

void		cast_rays(t_data *data);
void		init_ray(t_data *data, t_ray *ray, int x);

void		fill_background(t_data *data);
void		calc_line_height(t_data *data, t_ray *ray);
void		find_wall_x(t_data *data, t_ray *ray);
void		draw_wall_line(t_data *data, t_ray *ray);
uint32_t	get_color(t_data *data, t_ray *ray, int tex_x, int tex_y);

void		init_start_vars(t_data *data);
int			init_mlx(t_data *data);
int			clean_all(t_data *data);

void		draw_map(t_data *data);

void		mouse_look(t_data *data);
void		rotate(t_data *data, double dir);
void		move_forward(t_data *data);
void		move_backward(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);

void		register_hooks(t_data *data);

#endif