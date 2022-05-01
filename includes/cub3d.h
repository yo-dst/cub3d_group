#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "mlx.h"
# include "libft.h"

# define W 500
# define H 500

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
	char	**map;
	unsigned int	color_ceil;
	unsigned int	color_floor;
	/* next vars are for dev, to be replaced later with textures */
	unsigned int	color_ea;
	unsigned int	color_no;
	unsigned int	color_we;
	unsigned int	color_so;
	/* --- */
}	t_map;

typedef struct	s_info
{

}	t_info;

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

//	draw_scene.c
void	draw_scene(t_var *var);

#endif