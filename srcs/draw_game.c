#include "cub3d.h"

t_vec2	get_first_side_dist(t_var *v, t_vec2 ray_dir, t_vec2 unit_dist)
{
	t_vec2	side_dist;

	if (ray_dir.x > 0)
		side_dist.x = ((int)(v->player.x + 1) - v->player.x) * unit_dist.x;
	else
		side_dist.x = (v->player.x - (int)v->player.x) * unit_dist.x;
	if (ray_dir.y > 0)
		side_dist.y = ((int)(v->player.y + 1) - v->player.y) * unit_dist.y;
	else
		side_dist.y = (v->player.y - (int)v->player.y) * unit_dist.y;
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

double	get_wall_dist(t_var *v, t_vec2 ray_dir, int *side)
{
	t_vec2	step;
	t_vec2	curr_cell;
	t_vec2	unit_dist;
	t_vec2	side_dist;
	int		side_hit;

	step = get_step(ray_dir);
	curr_cell = get_vec2((int)v->player.x, (int)v->player.y);
	unit_dist.x = sqrt(1 + ((ray_dir.y / ray_dir.x) * (ray_dir.y / ray_dir.x)));
	unit_dist.y = sqrt(1 + ((ray_dir.x / ray_dir.y) * (ray_dir.x / ray_dir.y)));
	side_dist = get_first_side_dist(v, ray_dir, unit_dist);
	while (v->map[(int)curr_cell.y][(int)curr_cell.x] != WALL)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += unit_dist.x;
			curr_cell.x += step.x;
			side_hit = VERTICAL;
		}
		else
		{
			side_dist.y += unit_dist.y;
			curr_cell.y += step.y;
			side_hit = HORIZONTAL;
		}
	}
	if (side_hit == VERTICAL && step.x > 0)
		*side = EA;
	else if (side_hit == VERTICAL && step.x < 0)
		*side = WE;
	else if (side_hit == HORIZONTAL && step.y > 0)
		*side = SO;
	else if (side_hit == HORIZONTAL && step.y < 0)
		*side = NO;
	if (side_hit == VERTICAL)
		return (side_dist.x - unit_dist.x);
	return (side_dist.y - unit_dist.y);
}

int	get_wall_height(t_var *v, t_vec2 ray_dir, int *txtr_x, int *side)
{
	double	wall_dist;
	t_vec2	wall_hit;
	t_vec2	wall_vec;

	wall_dist = get_wall_dist(v, ray_dir, side);
	wall_hit = add_vec2(v->player, mult_vec2(ray_dir, wall_dist));
	wall_vec = get_vec2(wall_hit.x - v->player.x, wall_hit.y - v->player.y);
	wall_dist = wall_vec.x * v->player_dir.x + wall_vec.y * v->player_dir.y; // vector scalar projection to avoid fisheye effect
	if (*side == NO || *side == SO)
		*txtr_x = (int)((wall_hit.x - (int)wall_hit.x) * v->txtr[*side].w);
	else
		*txtr_x = (int)((wall_hit.y - (int)wall_hit.y) * v->txtr[*side].w);
	return ((double)H / wall_dist);
}

unsigned int	get_txtr_color(t_img txtr, int y, int txtr_x, double txtr_step_y)
{
	unsigned int	color;
	int				txtr_y;

	txtr_y = (int)(y * txtr_step_y);
	return (get_pixel_color(txtr, txtr_x, txtr_y));
}

void	draw_ray(t_var *v, int ray_x, t_vec2 ray_dir)
{
	int		wall_height;
	int		side;
	int		txtr_x;
	int		wall_start_y;
	int		y;

	wall_height = get_wall_height(v, ray_dir, &txtr_x, &side);
	wall_start_y = (H - wall_height) / 2;
	y = 0;
	while (y < wall_start_y)
		put_pixel(&v->screen, ray_x, y++, v->color[CEIL]);
	while (y < wall_start_y + wall_height)
	{
		//put_pixel(v, ray_x, y, v->color[side]);
		put_pixel(&v->screen, ray_x, y,
			get_pixel_color(v->txtr[side], txtr_x, (y - wall_start_y) * ((double)v->txtr[side].h / wall_height)));
			//get_txtr_color(v->txtr[side], y - top_wall, txtr_x, (double)v->txtr[side].h / wall_height));
		y++;
	}
	printf("here\n");
	while (y < H)
		put_pixel(&v->screen, ray_x, y++, v->color[FLOOR]);
	printf("here\n");
}

void	draw_rays(t_var *v)
{
	int		ray_x;
	double	camera_x;
	t_vec2	ray_dir;

	ray_x = 0;
	while (ray_x < W)
	{
		printf("%d\n", ray_x);
		camera_x = 2 * (double)ray_x / W - 1;
		ray_dir = add_vec2(v->player_dir, mult_vec2(v->camera, camera_x));
		ray_dir = norm_vec2(ray_dir);
		draw_ray(v, ray_x, ray_dir);
		ray_x++;
	}
}

void	draw_game(t_var *v)
{
	draw_rays(v);
	mlx_put_image_to_window(v->mlx, v->win, v->screen.img, 0, 0);
}
