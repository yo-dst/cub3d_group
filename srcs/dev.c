#include "cub3d.h"

void	test(t_var *v)
{
	printf("Ea = %s\n", v->txtr[EA].path);
	printf("No = %s\n", v->txtr[NO].path);
	printf("We = %s\n", v->txtr[WE].path);
	printf("So = %s\n", v->txtr[SO].path);
	printf("F = %u\n", v->color[FLOOR]);
	printf("C = %u\n", v->color[CEIL]);
	ft_puttabs(v->map, v->map_w, v->map_h);
}

void	ft_puttab(int *tab, int len)
{
    int i;

    i = 0;
	if (!tab || len <= 0)
		return ;
	while (len--)
    {
		ft_putnbr_fd(tab[i++], 1);
        ft_putchar_fd(' ', 1);
    }
    ft_putchar_fd('\n', 1);
}

void	ft_puttabs(int **tabs, int x, int y)
{
    int i;

    i = 0;
	if (!tabs || y <= 0)
		return ;
	while (y--)
		ft_puttab(tabs[i++], x);
}

void	ft_putstr_with_quote(char *str)
{
    int i;

    i = -1;
	if (!str)
		return ;
    while (str[++i])
        printf("'%c'\n", str[i]);
}

void	ft_putchars(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
    {
		ft_putstr_with_quote(strs[i]);
        ft_putstr("END\n");
    }
}
