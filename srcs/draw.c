#include "cub3d.h"

void	draw_circle(t_var *v, int x, int y, int radius, unsigned int color, int full)
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
				put_pixel(&v->screen, i, j, color);
			if (!full && dist >= radius * radius - 4 && dist <= radius * radius + 4)
				put_pixel(&v->screen, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_rect(t_var *v, int x, int y, int w, int h, unsigned int color)
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
				put_pixel(&v->screen, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_var *v, int x1, int y1, int x2, int y2)
{
	t_vec2	dir;
	t_vec2	curr_pixel;
	t_vec2	step;
	double	curr_dist;
	double	dist;
	t_vec2	unit_dist;
	t_vec2	side_dist;

	dir = get_vec2(x2 - x1, y2 - y1);
	dist = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir = get_vec2(dir.x / dist, dir.y / dist);
	unit_dist.x = sqrt(1 + ((dir.y / dir.x) * (dir.y / dir.x)));
	unit_dist.y = sqrt(1 + ((dir.x / dir.y) * (dir.x / dir.y)));
	curr_pixel = get_vec2(x1, y1);
	curr_dist = 0;
	side_dist = unit_dist;
	while (curr_dist < dist)
	{
		if (side_dist.x < side_dist.y)
		{
			curr_dist = side_dist.x;
			side_dist.x += unit_dist.x;
		}
		else
		{
			curr_dist = side_dist.y;
			side_dist.y += unit_dist.y;
		}
		curr_pixel = add_vec2(get_vec2(x1, y1), mult_vec2(dir, curr_dist));
		put_pixel(&v->screen, curr_pixel.x, curr_pixel.y, BLACK);
	}
}
