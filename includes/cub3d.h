#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include "X.h"

# define L 40
# define MAP_H 20
# define MAP_W 20
# define W (MAP_W * L)
# define H (MAP_H * L)

# define HORIZONTAL 0
# define VERTICAL 1

# define EMPTY 0
# define WALL 1

# define MOVE_SPEED 0.25

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_ESC 53


# define AZURE 0xf0ffff
# define BLACK 0x0
# define GOLD 0xffd700
# define GREEN_YELLOW 0xadff2f
# define INDIAN_RED 0xcd5c5c
# define PINK 0xffc0cb

typedef struct	s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_rgb;

typedef struct	s_map
{
	int				**map;
	unsigned int	color_ceil;
	unsigned int	color_floor;
	/* next vars are for dev, to be replaced later with textures */
	unsigned int	color_ea;
	unsigned int	color_no;
	unsigned int	color_we;
	unsigned int	color_so;
	/* --- */
}	t_map;

typedef struct	s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct	s_info
{
	
}	t_info;

typedef struct	s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	camera;
}	t_player;

typedef struct	s_var
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		endian;
	int		bpp;
	int		size_line;
	t_map	*map;
	t_info	*info;

	// test variables
	t_player	player;
	int		redisplay;
	int		mouse_x;
	int		mouse_y;
}	t_var;

//	parse_map.c
int		parse_map(t_map *map, char *map_file);

//	set_hooks.c
void	set_hooks(t_var *var);

//	init.c
int		init_game(t_var *var);
int		init_info(t_info *info);

//	print_error.c
void	print_error(char *msg);

//	utils.c
void			put_pixel(t_var *var, int x, int y, int color);
unsigned int	rgb_to_int(t_rgb rgb);

//	draw_game.c
void	draw_map(t_var *var);
void	draw_game(t_var *var);

//	draw.c
void	draw_circle(t_var *var, int x, int y, int radius, int color, int full);
void	draw_rect(t_var *var, int x, int y, int w, int h, int color);
void	draw_line(t_var *var, int x1, int y1, int x2, int y2);

//	init_map.c
void	init_map(int ***map);

//	vec2.c
void	set_vec2(t_vec2 *v, double x, double y);
t_vec2	get_vec2(double x, double y);
void	print_vec2(char *pfx, t_vec2 v);
t_vec2	add_vec2(t_vec2 v1, t_vec2 v2);
t_vec2	mult_vec2(t_vec2 v, float scalar);
t_vec2	norm_vec2(t_vec2 v);

#endif