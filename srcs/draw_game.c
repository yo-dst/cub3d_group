#include "cub3d.h"

t_vec2	get_first_side_dist(t_var *var, t_vec2 ray_dir, t_vec2 unit_dist)
{
	t_vec2	side_dist;

	if (ray_dir.x > 0)
		side_dist.x = ((int)(var->player.pos.x + 1) - var->player.pos.x) * unit_dist.x;
	else
		side_dist.x = (var->player.pos.x - (int)var->player.pos.x) * unit_dist.x;
	if (ray_dir.y > 0)
		side_dist.y = ((int)(var->player.pos.y + 1) - var->player.pos.y) * unit_dist.y;
	else
		side_dist.y = (var->player.pos.y - (int)var->player.pos.y) * unit_dist.y;
	return (side_dist);
}

t_vec2	get_step(t_vec2 ray_dir)
{
	t_vec2	step;

	if (ray_dir.x > 0)
		step.x = 1;
	else
		step.x = -1;
	if (ray_dir.y > 0)
		step.y = 1;
	else
		step.y = -1;
	return (step);
}

t_vec2	get_wall_hit(t_var *var, t_vec2 ray_dir)
{
	t_vec2	step;
	t_vec2	curr_cell;
	t_vec2	unit_dist;
	t_vec2	side_dist;
	double	curr_dist;

	step = get_step(ray_dir);
	curr_cell = get_vec2((int)var->player.pos.x, (int)var->player.pos.y);
	unit_dist.x = sqrt(1 + ((ray_dir.y / ray_dir.x) * (ray_dir.y / ray_dir.x)));
	unit_dist.y = sqrt(1 + ((ray_dir.x / ray_dir.y) * (ray_dir.x / ray_dir.y)));
	side_dist = get_first_side_dist(var, ray_dir, unit_dist);
	while (var->map->map[(int)curr_cell.y][(int)curr_cell.x] != WALL)
	{
		if (side_dist.x < side_dist.y)
		{
			curr_dist = side_dist.x;
			side_dist.x += unit_dist.x;
			curr_cell.x += step.x;
		}
		else
		{
			curr_dist = side_dist.y;
			side_dist.y += unit_dist.y;
			curr_cell.y += step.y;
		}
	}
	return (add_vec2(var->player.pos, mult_vec2(ray_dir, curr_dist)));
}

int	get_wall_height(t_var *var, t_vec2 ray_dir)
{
	t_vec2	wall_hit;
	t_vec2	wall_vec;
	double	wall_dist;
	int		wall_height;

	wall_hit = get_wall_hit(var, ray_dir);
	wall_dist = get_dist(var->player.pos, wall_hit);
	wall_vec = get_vec2(wall_hit.x - var->player.pos.x, wall_hit.y - var->player.pos.y);
	wall_dist = wall_vec.x * var->player.dir.x + wall_vec.y * var->player.dir.y; // vector scalar projection
	wall_height = (int)((double)H / wall_dist);
	return (wall_height);
}

void	draw_ray(t_var *var, int ray_x, t_vec2 ray_dir)
{
	int	wall_height;
	int	start;
	int	end;
	int	y;

	wall_height = get_wall_height(var, ray_dir);
	y = 0;
	start = (H - wall_height) / 2;
	end = H - start;
	while (y < start)
		put_pixel(var, ray_x, y++, var->map->color_ceil);
	while (y < end)
		put_pixel(var, ray_x, y++, INDIAN_RED);
	while (y < H)
		put_pixel(var, ray_x, y++, var->map->color_floor);
}

void	draw_rays(t_var *var)
{
	int		ray_x;
	double	camera_x;
	t_vec2	ray_dir;

	ray_x = 0;
	while (ray_x < W)
	{
		camera_x = 2 * (double)ray_x / W - 1;
		ray_dir = add_vec2(var->player.dir, mult_vec2(var->player.camera, camera_x));
		ray_dir = norm_vec2(ray_dir);
		draw_ray(var, ray_x, ray_dir);
		ray_x++;
	}
}

void	draw_game(t_var *var)
{
	draw_rays(var);
	mlx_put_image_to_window(var->mlx, var->win, var->img, 0, 0);
}
