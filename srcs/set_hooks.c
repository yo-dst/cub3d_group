#include "cub3d.h"

int	exit_game(t_var *var)
{
	int	i;

	i = 0;
	while (i < MAP_H)
		free(var->map->map[i++]);
	free(var->map->map);
	mlx_destroy_image(var->mlx, var->img);
	mlx_destroy_window(var->mlx, var->win);
	system("leaks cub3d");
	exit(0);
	return (0);
}

int	mouse_hook(int button, int x,int y, t_var *var)
{
	if (!(x >= 0 && x < W && y >= 0 && y < H))
		return (0);
	if (button == 1)
	{
		var->map->map[(int)(y / L)][(int)(x / L)] = !var->map->map[(int)(y / L)][(int)(x / L)];
		var->redisplay = 1;
	}
	return (0);
}

int	key_hook(int keycode, t_var *var)
{
	t_vec2	next_pos;

	if (keycode == KEY_ESC)
		exit_game(var);
	var->redisplay = 1;
	if (keycode == KEY_UP)
		next_pos = add_vec2(var->player.pos, mult_vec2(var->player.dir, MOVE_SPEED));
	else if (keycode == KEY_DOWN)
		next_pos = add_vec2(var->player.pos, mult_vec2(inv_vec2(var->player.dir), MOVE_SPEED));
	else if (keycode == KEY_RIGHT)
	{
		var->player.dir = rotate_vec2(var->player.dir, -ROTATE_SPEED);
		var->player.camera = rotate_vec2(var->player.camera, -ROTATE_SPEED);
	}
	else if (keycode == KEY_LEFT)
	{
		var->player.dir = rotate_vec2(var->player.dir, ROTATE_SPEED);
		var->player.camera = rotate_vec2(var->player.camera, ROTATE_SPEED);
	}
	else
		var->redisplay = 0;
	if ((keycode == KEY_UP || keycode == KEY_DOWN)
		&& var->map->map[(int)next_pos.y][(int)next_pos.x] != WALL)
		var->player.pos = next_pos;
	return (0);
}

int	mouse_motion_hook(int x, int y, t_var *var)
{
	var->redisplay = 1;
	mlx_mouse_get_pos(var->win, &var->mouse_x, &var->mouse_y);
	if (var->mouse_x < var->old_mouse_x)
	{
		var->player.dir = rotate_vec2(var->player.dir, ROTATE_SPEED);
		var->player.camera = rotate_vec2(var->player.camera, ROTATE_SPEED);
	}
	else if (var->mouse_x > var->old_mouse_x)
	{
		var->player.dir = rotate_vec2(var->player.dir, -ROTATE_SPEED);
		var->player.camera = rotate_vec2(var->player.camera, -ROTATE_SPEED);
	}
	else
		var->redisplay = 0;
	var->old_mouse_x = var->mouse_x;
	return (0);
}

int	loop_hook(t_var *var)
{
	// must limit fps
	if (var->redisplay)
	{
		//draw_map(var);
		draw_game(var);
		var->redisplay = 0;
	}
	return (0);
}

void	set_hooks(t_var *var)
{
	mlx_key_hook(var->win, &key_hook, var);
	mlx_hook(var->win, MotionNotify, 0, &mouse_motion_hook, var);
	//mlx_mouse_hook(var->win, &mouse_hook, var);
	mlx_hook(var->win, DestroyNotify, 0, &exit_game, var);
	mlx_loop_hook(var->mlx, &loop_hook, var);
}
