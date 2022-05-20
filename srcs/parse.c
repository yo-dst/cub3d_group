#include "cub3d.h"

int	parse(t_var *v, char *map_file)
{
	if (parse_file(v, map_file))
		return (1);
	test(v);
	v->color[NO] = INDIAN_RED;
	v->color[SO] = GREEN_YELLOW;
	v->color[EA] = GOLD;
	v->color[WE] = PINK;
	return (0);
}
