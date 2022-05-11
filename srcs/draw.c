#include "cub3d.h"

void	draw_circle(t_var *var, int x, int y, int radius, int color, int full)
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
			if (full && (dist <= radius * radius + 4))
				put_pixel(var, i, j, color);
			if (!full && dist >= radius * radius - 4 && dist <= radius * radius + 4)
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
