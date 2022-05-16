#include "cub3d.h"

int	main(int ac, char **av)
{
	t_var	v;

	if (!av || !*av || parse(&v, av[1]))
		return (1); // parse error
	if (init_game(&v))
		return (1); // init error
	v.mouse_moved = 0;
	set_hooks(&v);
	mlx_loop(v.mlx);
	return (0);
}
