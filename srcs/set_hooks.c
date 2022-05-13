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

int	mouse_motion_hook(int x, int y, t_var *var)
{
	var->redisplay = 1;
	mlx_mouse_get_pos(var->win, &var->mouse_x, &var->mouse_y);
	if (var->mouse_x < 0)
		var->mouse_x = 0;
	else if (var->mouse_x >= W)
		var->mouse_x = W - 1;
	if (var->mouse_x == 0 || var->mouse_x < var->old_mouse_x)
	{
		var->player.dir = rotate_vec2(var->player.dir, ROTATE_SPEED);
		var->player.camera = rotate_vec2(var->player.camera, ROTATE_SPEED);
	}
	else if (var->mouse_x == W - 1 || var->mouse_x > var->old_mouse_x)
	{
		var->player.dir = rotate_vec2(var->player.dir, -ROTATE_SPEED);
		var->player.camera = rotate_vec2(var->player.camera, -ROTATE_SPEED);
	}
	else
		var->redisplay = 0;
	var->old_mouse_x = var->mouse_x;
	return (0);
}

void	move_player(t_var *var, t_vec2 dir)
{
	t_vec2	next_pos;

	next_pos = add_vec2(var->player.pos, mult_vec2(dir, MOVE_SPEED));
	if (var->map->map[(int)next_pos.y][(int)next_pos.x] != WALL)
		var->player.pos = next_pos;
}

void	handle_key(t_var *var)
{
	if (var->key.z == PRESSED)
		move_player(var, var->player.dir);
	if (var->key.s == PRESSED)
		move_player(var, inv_vec2(var->player.dir));
	if (var->key.q == PRESSED)
		move_player(var, get_vec2(-var->player.dir.y, var->player.dir.x));
	if (var->key.d == PRESSED)
		move_player(var, get_vec2(var->player.dir.y, -var->player.dir.x));
	if (var->key.left == PRESSED)
	{
		var->player.dir = rotate_vec2(var->player.dir, ROTATE_SPEED);
		var->player.camera = rotate_vec2(var->player.camera, ROTATE_SPEED);
	}
	if (var->key.right == PRESSED)
	{
		var->player.dir = rotate_vec2(var->player.dir, -ROTATE_SPEED);
		var->player.camera = rotate_vec2(var->player.camera, -ROTATE_SPEED);
	}
}

int	key_is_pressed(t_key key)
{
	if (key.z == PRESSED || key.s == PRESSED || key.q == PRESSED
		|| key.d == PRESSED || key.left == PRESSED || key.right == PRESSED)
		return (1);
	return (0);
}

int	keypress_hook(int keycode, t_var *var)
{
	if (keycode == KEY_Z)
		var->key.z = PRESSED;
	else if (keycode == KEY_S)
		var->key.s = PRESSED;
	else if (keycode == KEY_Q)
		var->key.q = PRESSED;
	else if (keycode == KEY_D)
		var->key.d = PRESSED;
	else if (keycode == KEY_LEFT)
		var->key.left = PRESSED;
	else if (keycode == KEY_RIGHT)
		var->key.right = PRESSED;
	return (0);
}

int	keyrelease_hook(int keycode, t_var *var)
{
	if (keycode == KEY_ESC)
		exit_game(var);
	if (keycode == KEY_Z)
		var->key.z = RELEASED;
	else if (keycode == KEY_S)
		var->key.s = RELEASED;
	else if (keycode == KEY_Q)
		var->key.q = RELEASED;
	else if (keycode == KEY_D)
		var->key.d = RELEASED;
	else if (keycode == KEY_LEFT)
		var->key.left = RELEASED;
	else if (keycode == KEY_RIGHT)
		var->key.right = RELEASED;
	return (0);
}

int	loop_hook(t_var *var)
{
	long	t;

	t = get_time();
	if (time_diff(var->t_last_frame, t) > T_PER_FRAME
		&& (var->redisplay || key_is_pressed(var->key)))
	{
		handle_key(var);
		draw_game(var);
		var->t_last_frame = t;
		var->redisplay = 0;
	}
	return (0);
}

void	set_hooks(t_var *var)
{
	mlx_hook(var->win, MotionNotify, 0, &mouse_motion_hook, var);
	mlx_hook(var->win, KeyPress, 0, &keypress_hook, var);
	mlx_hook(var->win, KeyRelease, 0, &keyrelease_hook, var);
	mlx_hook(var->win, DestroyNotify, 0, &exit_game, var);
	mlx_loop_hook(var->mlx, &loop_hook, var);
}
