#include "cub3d.h"

void	draw_circle(t_img *img, int x, int y, int radius, unsigned int color, int full)
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
				put_pixel(img, i, j, color);
			if (!full && dist >= radius * radius - 4 && dist <= radius * radius + 4)
				put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_rect(t_img *img, int x, int y, int w, int h, unsigned int color)
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
				put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_line(t_img *img, int x1, int y1, int x2, int y2)
{
	t_vec2	dir; // direction of 
	t_vec2	curr_pixel;
	t_vec2	step;
	double	curr_dist;
	double	dist;
	t_vec2	unit_dist;
	t_vec2	side_dist;

	// we define A(x1, y1) and B(x2, y2)
	dir = get_vec2(x2 - x1, y2 - y1); // calc vector AB
	dist = sqrt(dir.x * dir.x + dir.y * dir.y); // calc magnitude/distance of AB
	dir = get_vec2(dir.x / dist, dir.y / dist); // normalize AB so it's magnitude = 1
	// now 'dir' represents the direction of AB
	// we define V(x, y) a vector having the same direction than 'dir' 
	unit_dist.x = sqrt(1 + ((dir.y / dir.x) * (dir.y / dir.x))); // calc magnitude of V if V.x = 1
	unit_dist.y = sqrt(1 + ((dir.x / dir.y) * (dir.x / dir.y))); // calc magnitude of V if V.y = 1
	curr_pixel = get_vec2(x1, y1); // set the pixel we're examining to A coordinates
	curr_dist = 0;
	side_dist = unit_dist; // we're raycasting on pixels, x1;y1 are intergers, so the first 'side_dist' = 'unit_dist'
	// if x1;y1 were floats then the first 'side_dist' would be easy to calculate :
	// - if ray going right : side_dist.x = (int)(x1 + 1) - x1;
	// - if ray going down : side_dist.y = y1 - (int)y1;
	// - ...
	//
	// how do you know ray direction?
	// - dir.x > 0 => going right
	// - dir.y < 0 => going down
	// - ...
	while (curr_dist < dist)
	{
		if (side_dist.x < side_dist.y) // means that : 'dist from vertical intersection' < 'dist from horizontal intersection'
		{
			curr_dist = side_dist.x; // we keep the distance
			side_dist.x += unit_dist.x; // we set 'side_dist.x' to the distance from the next vertical intersection
		}
		else
		{
			curr_dist = side_dist.y;
			side_dist.y += unit_dist.y;
		}
		curr_pixel = add_vec2(get_vec2(x1, y1), mult_vec2(dir, curr_dist)); // we get coordinate of pixel we reach at 'curr_dist'
		put_pixel(img, curr_pixel.x, curr_pixel.y, BLACK);
	}
}
