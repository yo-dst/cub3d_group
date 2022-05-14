#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include "X.h"
# include <sys/time.h>

# define TXTR_W 100
# define TXTR_H 100

# define MAP_H 20
# define MAP_W 20
# define W 800
# define H 800

# define T_PER_FRAME (1000.0 / 60)

# define HORIZONTAL 0
# define VERTICAL 1

# define PRESSED 0
# define RELEASED 1

# define EMPTY 0
# define WALL 1

# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.03

# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_ESC 53
# define KEY_Z 13
# define KEY_S 1
# define KEY_Q 0
# define KEY_D 2

# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define CEIL 4
# define FLOOR 5

# define AZURE 0xf0ffff
# define BLACK 0x0
# define GOLD 0xffd700
# define GREEN_YELLOW 0xadff2f
# define INDIAN_RED 0xcd5c5c
# define PINK 0xffc0cb

typedef struct s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_rgb;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_key
{	
	int	z;
	int	s;
	int	q;
	int	d;
	int	left;
	int	right;
}	t_key;

typedef struct s_txtr
{
	void	*img;
	char	*data;
	int		w;
	int		h;
	int		size_line;
}	t_txtr;

typedef struct s_var
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_data;
	int				endian;
	int				bpp;
	int				size_line;
	int				redisplay;
	int				mouse_x;
	int				mouse_y;
	int				old_mouse_x;
	long			t_last_frame;
	t_key			key;
	int				**map;
	unsigned int	color[6];
	t_vec2			player;
	t_vec2			player_dir;
	t_vec2			camera;
	t_txtr			txtr[6];

	// utils to raycast algo
}	t_var;

//	parse_map.c
int		parse(t_var *v, char *map_file);

//	set_hooks.c
void	set_hooks(t_var *v);

//	init.c
int		init_game(t_var *v);
int		init_txtr(t_var *v);

//	print_error.c
void	print_error(char *msg);

//	utils.c
void			put_pixel(t_var *v, int x, int y, int color);
unsigned int	rgb_to_int(t_rgb rgb);
double			get_dist(t_vec2 v1, t_vec2 v2);
unsigned int	get_pixel_color(char *img_data, int x, int y, int size_line);

//	draw_game.c
void	draw_map(t_var *v);
void	draw_game(t_var *v);

//	draw.c
void	draw_circle(t_var *v, int x, int y, int radius, int color, int full);
void	draw_rect(t_var *v, int x, int y, int w, int h, int color);
void	draw_line(t_var *v, int x1, int y1, int x2, int y2);

//	init_map.c
void	init_map(int ***map);

//	vec2.c
void	set_vec2(t_vec2 *v, double x, double y);
t_vec2	get_vec2(double x, double y);
void	print_vec2(char *pfx, t_vec2 v);
t_vec2	add_vec2(t_vec2 v1, t_vec2 v2);
t_vec2	mult_vec2(t_vec2 v, float scalar);
t_vec2	norm_vec2(t_vec2 v);
t_vec2	inv_vec2(t_vec2 v);
t_vec2	rotate_vec2(t_vec2 v, double angle);

//	time.c
long	get_time(void);
long	time_diff(long start, long end);

#endif