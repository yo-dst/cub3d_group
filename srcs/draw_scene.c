#include "cub3d.h"

t_vec2	plyr;

void	set_vec2(t_vec2 *v, float x, float y)
{
	v->x = x;
	v->y = y;
}

t_vec2	get_vec2(float x, float y)
{
	t_vec2	res;

	res.x = x;
	res.y = y;
	return (res);
}

void	print_vec2(char *pfx, t_vec2 v)
{
	if (pfx)
		printf("%s: ", pfx);
	printf("(%f, %f)", v.x, v.y);
}

t_vec2	add_vec2(t_vec2 v1, t_vec2 v2)
{
	t_vec2	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	return (res);
}

t_vec2	mult_vec2(t_vec2 v, float scalar)
{
	t_vec2	res;

	res.x = v.x * scalar;
	res.y = v.y * scalar;
	return (res);
}

int	raycast(t_var *var)
{
	int		hit;
	int		side;
	t_vec2	step;
	int		ray_x;
	t_vec2	player_dir;
	t_vec2	camera;
	t_vec2	ray_dir;
	t_vec2	player_pos;
	t_vec2	map_pos;
	t_vec2	side_dist;
	double	inter_dist;
	t_vec2	unit_dist;
	double	camera_x;

	set_vec2(&player_pos, 2, 2);
	set_vec2(&player_dir, 0, 1);
	set_vec2(&camera, 0.66, 0);
	ray_x = 0;
	while (ray_x < W)
	{
		set_vec2(&map_pos, (int)player_pos.x, (int)player_pos.y);
		camera_x = 2 * (double)ray_x / W - 1; 
		//printf("%f\n", camera_x);
		ray_dir = add_vec2(player_dir, mult_vec2(camera, camera_x));
		unit_dist.x = sqrt(1 + (ray_dir.y * ray_dir.y  / ray_dir.x * ray_dir.x));
		unit_dist.y = sqrt((ray_dir.x * ray_dir.x / ray_dir.y * ray_dir.y) + 1);               
		if (ray_dir.x > 0)
		{
			side_dist.x = ((int)(player_pos.x + 1) - player_pos.x) * unit_dist.x;
			step.x = 1;
		}
		else
		{
			side_dist.x = (player_pos.x - (int)player_pos.x) * unit_dist.x;
			step.x = -1;
		}
		if (ray_dir.y > 0)
		{
			side_dist.y = ((int)(player_pos.y + 1) - player_pos.y) * unit_dist.y;
			step.y = 1;
		}
		else
		{
			side_dist.y = (player_pos.y - (int)player_pos.y) * unit_dist.y;
			step.y = -1;
		}
		hit = 0;
		while (!hit)
		{
			if (side_dist.x < side_dist.y)
			{
				inter_dist = side_dist.x;
				side_dist.x += unit_dist.x;
				map_pos.x += step.x;
				side = HORIZONTAL;
			}
			else
			{
				inter_dist = side_dist.y;
				side_dist.y += unit_dist.y;
				map_pos.y += step.y;
				side = VERTICAL;
			}
			if (var->map->map[(int)map_pos.y][(int)map_pos.x] == WALL)
				hit = 1;
		}
		printf("%d | %d | %f | (%d, %d) | ", ray_x, side, inter_dist, (int)map_pos.x, (int)map_pos.y);
		print_vec2(NULL, ray_dir);
		printf("\n");
		ray_x++;
	}
	return (0);
}

void	draw_player(t_var *var)
{
	draw_circle(var, var->player.x, var->player.y, 5, INDIAN_RED);
}

void	draw_mouse(t_var *var)
{
	int	mouse_x;
	int	mouse_y;

	mlx_mouse_get_pos(var->win, &mouse_x, &mouse_y);
	draw_circle(var, mouse_x, mouse_y, 5, BLACK);
}

void	draw_map(t_var *var)
{
	int	i;
	int	j;
	int	block_w;
	int	block_h;

	i = 0;
	while (i < L * MAP_W)
	{
		j = 0;
		while (j < L * MAP_H)
		{
			if (i % L == 0 || j % L == 0)
				put_pixel(var, i, j, BLACK);
			else if (var->map->map[(int)(j / L)][(int)(i / L)] == WALL)
				put_pixel(var, i, j, GOLD);
			else
				put_pixel(var, i, j, PINK);
			j++;
		}
		i++;
	}
	draw_player(var);
	draw_mouse(var);
	mlx_put_image_to_window(var->mlx, var->win, var->img, 0, 0);
}

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
