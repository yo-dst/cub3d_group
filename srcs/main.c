/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:04:40 by ydanset           #+#    #+#             */
/*   Updated: 2022/06/01 11:49:45 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_var	v;

	if (!av || !*av || parse(&v, av[1]))
		return (1);
	if (init_game(&v))
		return (1);
	set_hooks(&v);
	mlx_loop(v.mlx);
	return (0);
}
