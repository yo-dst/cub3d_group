/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydanset <ydanset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:04:40 by ydanset           #+#    #+#             */
/*   Updated: 2022/06/01 11:04:41 by ydanset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_var	v;

	if (!av || !*av || parse(&v, av[1]))
		return (1); // parse error
	if (init_game(&v))
		return (1); // init error
	set_hooks(&v);
	mlx_loop(v.mlx);
	return (0);
}
