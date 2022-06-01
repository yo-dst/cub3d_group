/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:58:34 by ydanset           #+#    #+#             */
/*   Updated: 2022/06/01 13:15:45 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	write(1, str, ft_strlen(str));
}

void	ft_putstrs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		ft_putstr(strs[i]);
}

void	ft_putendl_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		ft_putendl_fd(strs[i++], 1);
}
