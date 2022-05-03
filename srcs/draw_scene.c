#include "cub3d.h"

void	draw_scene(t_var *var)
{
	int	i;
	int	j;
	int	x1, x2, y1, y2;
	
	x1 = 100;
	y1 = 150;
	x2 = 105;
	y2 = 175;
	double m = (y2 - y1) / (x2 - x1);
	double c = y1 - m * x1;
	printf("m: %f | c: %f\n", m, c);
	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			if (j == (int)(m * (double)i + c))
			{
				printf("on line\n");
				put_pixel(var, i, j, BLACK);
			}
			else
				put_pixel(var, i, j, GOLD);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(var->mlx, var->win, var->img, 0, 0);
}
