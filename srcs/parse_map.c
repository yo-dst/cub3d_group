#include "cub3d.h"

int	parse_map(t_map *map, char *map_file)
{
	if (!map_file)
	{
		print_error("missing parameter");
		return (1);
	}
	// temporary
	map->color_ea = GOLD;
	map->color_no = INDIAN_RED;
	map->color_we = GREEN_YELLOW;
	map->color_so = PINK;
	map->color_ceil = AZURE;
	map->color_floor = BLACK;
	//
	return (0);
}
