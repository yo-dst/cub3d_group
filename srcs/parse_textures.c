/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:04:44 by ydanset           #+#    #+#             */
/*   Updated: 2022/06/01 13:05:42 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_collor(char *words, unsigned int *color)
{
	char		**rgb;
	int			i;
	long long	check;
	char		*hexa_rgb;

	i = -1;
	hexa_rgb = NULL;
	if (*color != -42 || multiple_comma(words))
		return (1);
	rgb = ft_split(words, ',');
	if (ft_strslen(rgb) != 3 || number_too_long(rgb))
		return (free_color_error(rgb, "RGB Error : ", hexa_rgb));
	while (rgb[++i])
	{
		check = ft_atoi_long_long(rgb[i]);
		if (check > 255 || check < 0)
			return (free_color_error(rgb, "RGB Error : ", hexa_rgb));
		hexa_rgb = ft_join_free_ss(hexa_rgb, ft_itoa_base(check, HEX));
	}
	*color = ft_atoi_base(hexa_rgb, HEX);
	ft_free_strs(rgb);
	free(hexa_rgb);
	free(words);
	return (0);
}

char	*join_words(char **words)
{
	char	*str;
	int		i;

	i = -1;
	str = NULL;
	while (words[++i])
		str = ft_join_free_s1(str, words[i]);
	return (str);
}

int	check_and_assign(char **words, t_var *v)
{
	if (!ft_strncmp(words[0], "NO", 2) && !v->txtr[NO].path)
		v->txtr[NO].path = ft_strdup(words[1]);
	else if (!ft_strncmp(words[0], "EA", 2) && !v->txtr[SO].path)
		v->txtr[SO].path = ft_strdup(words[1]);
	else if (!ft_strncmp(words[0], "SO", 2) && !v->txtr[EA].path)
		v->txtr[EA].path = ft_strdup(words[1]);
	else if (!ft_strncmp(words[0], "WE", 2) && !v->txtr[WE].path)
		v->txtr[WE].path = ft_strdup(words[1]);
	else if (!ft_strncmp(words[0], "F", 1))
		return (assign_collor(join_words(&words[1]), &(v->color[FLOOR])));
	else if (!ft_strncmp(words[0], "C", 1))
		return (assign_collor(join_words(&words[1]), &(v->color[CEIL])));
	else
		return (1);
	return (0);
}

int	free_textures_error(t_var *v, char *msg, char **words)
{
	free(v->txtr[NO].path);
	free(v->txtr[SO].path);
	free(v->txtr[EA].path);
	free(v->txtr[WE].path);
	ft_free_strs(words);
	return (print_and_return_error(msg));
}

int	parse_textures(t_var *v, char **textures)
{
	char	**words;
	int		i;

	i = -1;
	if (ft_strslen(textures) != 6)
		return (print_and_return_error("Invalid textures"));
	while (textures[++i])
	{
		words = ft_split(textures[i], ' ');
		if (ft_strlen(words[0]) > 2)
			return (free_textures_error(v, "Invalid textures", words));
		else if (check_and_assign(words, v))
			return (free_textures_error(v, "Invalid textures", words));
		ft_free_strs(words);
	}
	return (0);
}
