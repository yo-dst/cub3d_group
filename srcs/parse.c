#include "cub3d.h"

int	parse(t_var *var, char *map_file)
{
	if (!map_file)
	{
		print_error("missing parameter");
		return (1);
	}
	init_map(&var->map);
	var->color[NO] = INDIAN_RED;
	var->color[SO] = GREEN_YELLOW;
	var->color[EA] = GOLD;
	var->color[WE] = PINK;
	var->color[CEIL] = AZURE;
	var->color[FLOOR] = BLACK;
	return (0);
}
