#include "cub3d.h"

void	draw_player(t_var *var)
{
	draw_circle(var, var->player.pos.x * L, var->player.pos.y * L, 5, INDIAN_RED, 1);
}

void	draw_mouse(t_var *var)
{
	draw_circle(var, var->mouse_x, var->mouse_y, 5, BLACK, 1);
}

t_vec2	get_pos_wall(t_var *var)
{
	int		hit;
	t_vec2	dir;
	t_vec2	step;
	double	curr_dist;
	double	magnitude;
	t_vec2	curr_cell;
	t_vec2	mouse;
	t_vec2	side_dist; // distance between player and first horizontal (y) and vertical (x) intersections.
	t_vec2	unit_dist;

	mouse = get_vec2((double)var->mouse_x / L, (double)var->mouse_y / L); // scale mouse coordinate
	dir = get_vec2(mouse.x - var->player.pos.x, mouse.y - var->player.pos.y); // get vector between mouse and player
	magnitude = sqrt(dir.x * dir.x + dir.y * dir.y); // get magnitude of this vector
	dir = get_vec2(dir.x / magnitude, dir.y / magnitude); // normalize direction
	curr_cell = get_vec2((int)var->player.pos.x, (int)var->player.pos.y); // current map cell we check
	unit_dist.x = sqrt(1 + ((dir.y / dir.x) * (dir.y / dir.x))); // if i move one cell on x plane, i'll move 'unit_dist.x' in 'dir' direction
	unit_dist.y = sqrt(1 + ((dir.x / dir.y) * (dir.x / dir.y)));
	if (dir.x > 0)
	{
		side_dist.x = ((int)(var->player.pos.x + 1) - var->player.pos.x) * unit_dist.x;
		step.x = 1;
	}
	else
	{
		side_dist.x = (var->player.pos.x - (int)var->player.pos.x) * unit_dist.x;
		step.x = -1;
	}
	if (dir.y > 0)
	{
		side_dist.y = ((int)(var->player.pos.y + 1) - var->player.pos.y) * unit_dist.y;
		step.y = 1;
	}
	else
	{
		side_dist.y = (var->player.pos.y - (int)var->player.pos.y) * unit_dist.y;
		step.y = -1;
	}
	hit = 0;
	while (!hit)
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
		if (var->map->map[(int)curr_cell.y][(int)curr_cell.x] == WALL)
			hit = 1;
	}
	return (add_vec2(var->player.pos, mult_vec2(dir, curr_dist)));
}

void	draw_map(t_var *var)
{
	int	i;
	int	j;
	int	block_w;
	int	block_h;
	t_vec2	wall;

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
	draw_line(var, var->player.pos.x * L, var->player.pos.y * L, var->mouse_x, var->mouse_y);
	draw_player(var);
	draw_mouse(var);
	wall = get_pos_wall(var);
	draw_circle(var, wall.x * L, wall.y * L, 5, BLACK, 0);
	mlx_put_image_to_window(var->mlx, var->win, var->img, 0, 0);
}

// -----------------------------------------------

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
	double	wall_dist;
	int		wall_height;

	wall_hit = get_wall_hit(var, ray_dir);
	wall_dist = get_dist(var->player.pos, wall_hit);
	// find wall height
	return (wall_height);
}

void	draw_ray(t_var *var, t_vec2 ray_dir)
{
	int	wall_height;

	wall_height = get_wall_height(var, ray_dir);
	// draw ray
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
		draw_ray(var, ray_dir);
		ray_x++;
	}
}

void	draw_game(t_var *var)
{
	draw_rays(var);
}