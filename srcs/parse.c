#include "cub3d.h"

void	init_without_error(t_var *v)
{
	int	i;
	int j;
	
	v->map_w = MAP_W;
	v->map_h = MAP_H;
	v->map = malloc(sizeof(int *) * v->map_h);
	i = 0;
	while (i < v->map_h)
		v->map[i++] = malloc(sizeof(int) * v->map_w);
	i = 0;
	while (i < v->map_h)
	{
		j = 0;
		while (j < v->map_w)
		{
			if (i == 0 || i == v->map_h - 1 || j == 0 || j == v->map_w - 1)
				v->map[i][j] = WALL;
			else
				v->map[i][j] = EMPTY;
			j++;
		}
		i++;
	}
	v->player = get_vec2(MAP_W / 2, MAP_H / 2);
    v->player_dir = get_vec2(0, 1);
    v->camera = get_vec2(0.66, 0);
	v->color[FLOOR] = BLACK;
	v->color[CEIL] = GREEN_YELLOW;
}

int	parse(t_var *v, char *map_file)
{
	
	if (parse_file(v, map_file))
		return (1);
	v->color[NO] = INDIAN_RED;
	v->color[SO] = GREEN_YELLOW;
	v->color[EA] = GOLD;
	v->color[WE] = PINK;
	return (0);
}
