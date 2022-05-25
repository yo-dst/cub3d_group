#include "cub3d.h"

int	parse(t_var *v, char *map_file)
{
	
	if (parse_file(v, map_file))
		return (1);
	return (0);
}
