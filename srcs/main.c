#include "cub3d.h"

int		raycast();
void	draw_map(t_var *var);
void	draw_player(t_var *var);

void	test()
{
	double	x = 124234.343;

	printf("%f\n", x);
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
	var.player.x = (W / 2);
	var.player.y = (H / 2);
	var.redisplay = 0;
	//raycast(&var);
	draw_map(&var);
	//draw_scene(&var);
	set_hooks(&var);
	mlx_loop(var.mlx);
	printf("working on it :)\n");
	return (0);
}
