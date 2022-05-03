#include "cub3d.h"

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
	
	//test();
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
	draw_scene(&var);
	set_hooks(&var);
	mlx_loop(var.mlx);
	printf("working on it :)\n");
	return (0);
}
