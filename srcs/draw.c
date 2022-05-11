#include "cub3d.h"

void	draw_circle(t_var *var, int x, int y, int radius, int color)
{
	int	i;
	int	j;
	int	dist;

	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			dist = (x - i) * (x - i) + (y - j) * (y - j);
			if (dist <= radius * radius)
				put_pixel(var, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_rect(t_var *var, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			if (i >= x && i < x + w && j >= y && j < y + h)
				put_pixel(var, i, j, color);
			j++;
		}
		i++;
	}
}
