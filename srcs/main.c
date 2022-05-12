#include "cub3d.h"

void	test()
{
	exit(0);
}

int	main(int ac, char **av)
{
	t_var	var;
	t_map	map;
	t_info	info;
	
	if (!av || !*av || parse_map(&map, av[1]))
		return (1); // parse error
	init_info(&info);
	var.map = &map;
	var.info = &info;
	if (init_game(&var))
	{
		print_error("failed to initialize mlx");
		return (1); // mlx error
	}
	init_map(&(var.map)->map);
	var.redisplay = 1;
	var.player.pos = get_vec2(W / 2 / L, H / 2 / L);
	var.player.dir = get_vec2(0, 1);
	var.player.camera = get_vec2(0.66, 0);
	mlx_mouse_move(var.win, W / 2, H / 2);
	mlx_mouse_get_pos(var.win, &var.mouse_x, &var.mouse_y);
	set_hooks(&var);
	mlx_loop(var.mlx);
	printf("working on it :)\n");
	return (0);
}
