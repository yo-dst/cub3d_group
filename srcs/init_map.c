#include "cub3d.h"

void	init_map(int ***map)
{
	int	i;
	int	j;

	*map = malloc(sizeof(int *) * MAP_H);
	i = 0;
	while (i < MAP_H)
		(*map)[i++] = malloc(sizeof(int) * MAP_W);
	i = 0;
	while (i < MAP_W)
	{
		j = 0;
		while (j < MAP_H)
		{
			if (i == 0 || i == MAP_W - 1 || j == 0 || j == MAP_H - 1)
				(*map)[j][i] = WALL;
			else
				(*map)[j][i] = EMPTY;
			j++;
		}
		i++;
	}
}
