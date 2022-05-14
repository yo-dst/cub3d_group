#include "cub3d.h"

int	exit_game(t_var *v)
{
	int	i;

	i = 0;
	while (i < MAP_H)
		free(v->map[i++]);
	free(v->map);
	mlx_destroy_image(v->mlx, v->img);
	mlx_destroy_window(v->mlx, v->win);
	system("leaks cub3d");
	exit(0);
	return (0);
}

int	mouse_motion_hook(int x, int y, t_var *v)
{
	v->redisplay = 1;
	mlx_mouse_get_pos(v->win, &v->mouse_x, &v->mouse_y);
	if (v->key.left != PRESSED
		&& (v->mouse_x < v->old_mouse_x
		|| (v->mouse_x < 0 && v->mouse_x == v->old_mouse_x)))
	{
		v->player_dir = rotate_vec2(v->player_dir, ROTATE_SPEED);
		v->camera = rotate_vec2(v->camera, ROTATE_SPEED);
	}
	else if (v->key.right != PRESSED
		&& (v->mouse_x > v->old_mouse_x
		|| (v->mouse_x >= W && v->mouse_x == v->old_mouse_x)))
	{
		v->player_dir = rotate_vec2(v->player_dir, -ROTATE_SPEED);
		v->camera = rotate_vec2(v->camera, -ROTATE_SPEED);
	}
	else
		v->redisplay = 0;
	v->old_mouse_x = v->mouse_x;
	return (0);
}

void	move_player(t_var *v, t_vec2 dir)
{
	t_vec2	next_pos;

	next_pos = add_vec2(v->player, mult_vec2(dir, MOVE_SPEED));
	if (v->map[(int)next_pos.y][(int)next_pos.x] != WALL)
		v->player = next_pos;
}

void	handle_key(t_var *v)
{
	if (v->key.z == PRESSED)
		move_player(v, v->player_dir);
	if (v->key.s == PRESSED)
		move_player(v, inv_vec2(v->player_dir));
	if (v->key.q == PRESSED)
		move_player(v, get_vec2(-v->player_dir.y, v->player_dir.x));
	if (v->key.d == PRESSED)
		move_player(v, get_vec2(v->player_dir.y, -v->player_dir.x));
	if (v->key.left == PRESSED)
	{
		v->player_dir = rotate_vec2(v->player_dir, ROTATE_SPEED);
		v->camera = rotate_vec2(v->camera, ROTATE_SPEED);
	}
	if (v->key.right == PRESSED)
	{
		v->player_dir = rotate_vec2(v->player_dir, -ROTATE_SPEED);
		v->camera = rotate_vec2(v->camera, -ROTATE_SPEED);
	}
}

int	key_is_pressed(t_key key)
{
	if (key.z == PRESSED || key.s == PRESSED || key.q == PRESSED
		|| key.d == PRESSED || key.left == PRESSED || key.right == PRESSED)
		return (1);
	return (0);
}

int	keypress_hook(int keycode, t_var *v)
{
	if (keycode == KEY_Z)
		v->key.z = PRESSED;
	else if (keycode == KEY_S)
		v->key.s = PRESSED;
	else if (keycode == KEY_Q)
		v->key.q = PRESSED;
	else if (keycode == KEY_D)
		v->key.d = PRESSED;
	else if (keycode == KEY_LEFT)
		v->key.left = PRESSED;
	else if (keycode == KEY_RIGHT)
		v->key.right = PRESSED;
	return (0);
}

int	keyrelease_hook(int keycode, t_var *v)
{
	if (keycode == KEY_ESC)
		exit_game(v);
	if (keycode == KEY_Z)
		v->key.z = RELEASED;
	else if (keycode == KEY_S)
		v->key.s = RELEASED;
	else if (keycode == KEY_Q)
		v->key.q = RELEASED;
	else if (keycode == KEY_D)
		v->key.d = RELEASED;
	else if (keycode == KEY_LEFT)
		v->key.left = RELEASED;
	else if (keycode == KEY_RIGHT)
		v->key.right = RELEASED;
	return (0);
}

int	loop_hook(t_var *v)
{
	long	t;

	t = get_time();
	if (time_diff(v->t_last_frame, t) > T_PER_FRAME
		&& (v->redisplay || key_is_pressed(v->key)))
	{
		handle_key(v);
		draw_game(v);
		v->t_last_frame = t;
		v->redisplay = 0;
	}
	return (0);
}

void	set_hooks(t_var *v)
{
	mlx_hook(v->win, MotionNotify, 0, &mouse_motion_hook, v);
	mlx_hook(v->win, KeyPress, 0, &keypress_hook, v);
	mlx_hook(v->win, KeyRelease, 0, &keyrelease_hook, v);
	mlx_hook(v->win, DestroyNotify, 0, &exit_game, v);
	mlx_loop_hook(v->mlx, &loop_hook, v);
}
