#include "cub3d.h"

void	draw_scene(t_var *var)
{
	int	i;
	int	j;

	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			put_pixel(var, i, j, GOLD);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(var->mlx, var->win, var->img, 0, 0);
}
