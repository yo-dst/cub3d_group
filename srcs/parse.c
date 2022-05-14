#include "cub3d.h"

int	parse(t_var *v, char *map_file)
{
	if (!map_file)
	{
		print_error("missing parameter");
		return (1);
	}
	init_map(&v->map);
	v->color[NO] = INDIAN_RED;
	v->color[SO] = GREEN_YELLOW;
	v->color[EA] = GOLD;
	v->color[WE] = PINK;
	v->color[CEIL] = AZURE;
	v->color[FLOOR] = BLACK;
	v->player = get_vec2(MAP_W / 2, MAP_H / 2);
	v->player_dir = get_vec2(0, 1);
	v->camera = get_vec2(0.66, 0);
	return (0);
}
