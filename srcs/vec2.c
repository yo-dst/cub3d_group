#include "cub3d.h"

void	set_vec2(t_vec2 *v, double x, double y)
{
	v->x = x;
	v->y = y;
}

t_vec2	get_vec2(double x, double y)
{
	t_vec2	res;

	res.x = x;
	res.y = y;
	return (res);
}

void	print_vec2(char *pfx, t_vec2 v)
{
	if (pfx)
		printf("%s: ", pfx);
	printf("(%f, %f)\n", v.x, v.y);
}

t_vec2	add_vec2(t_vec2 v1, t_vec2 v2)
{
	t_vec2	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	return (res);
}

t_vec2	mult_vec2(t_vec2 v, float scalar)
{
	t_vec2	res;

	res.x = v.x * scalar;
	res.y = v.y * scalar;
	return (res);
}

t_vec2	norm_vec2(t_vec2 v)
{
	t_vec2	res;
	double	magnitude;

	magnitude = sqrt(v.x * v.x + v.y * v.y);
	res.x = v.x / magnitude;
	res.y = v.y / magnitude;
	return (res);
}

t_vec2	inv_vec2(t_vec2 v)
{
	t_vec2	res;

	res.x = v.x * -1;
	res.y = v.y * -1;
	return (res);
}

// angle must be in radian
t_vec2	rotate_vec2(t_vec2 v, double angle)
{
	t_vec2	res;

	res.x = v.x * cos(angle) - v.y * sin(angle);
	res.y = v.x * sin(angle) + v.y * cos(angle);
	return (res);
}
