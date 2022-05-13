#include "cub3d.h"

void	put_pixel(t_var *var, int x, int y, int color)
{
	int	index_pixel;

	if (x < 0 || x >= W || y < 0 || y >= H)
		return ;
	index_pixel = y * var->size_line + x * 4;
	if (var->endian == 1)
	{
		var->img_data[index_pixel] = (color >> 24);
		var->img_data[index_pixel + 1] = (color >> 16) & 0xFF;
		var->img_data[index_pixel + 2] = (color >> 8) & 0xFF;
		var->img_data[index_pixel + 3] = (color) & 0xFF;
	}
	else
	{
		var->img_data[index_pixel] = (color) & 0xFF;
		var->img_data[index_pixel + 1] = (color >> 8) & 0xFF;
		var->img_data[index_pixel + 2] = (color >> 16) & 0xFF;
		var->img_data[index_pixel + 3] = (color >> 24);
	}
}

unsigned int	rgb_to_int(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

double	get_dist(t_vec2 v1, t_vec2 v2)
{
	return (sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y)));
}