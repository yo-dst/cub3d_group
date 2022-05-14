#include "cub3d.h"

void	init_key(t_key *key)
{
	key->z = RELEASED;
	key->s = RELEASED;
	key->q = RELEASED;
	key->d = RELEASED;
	key->left = RELEASED;
	key->right = RELEASED;
}

int	load_txtr(t_var *v, char *filename, t_txtr *txtr)
{
	char	*err_msg;
	char	*tmp;

	txtr->img = mlx_xpm_file_to_image(v->mlx, filename, &txtr->w, &txtr->h);
	if (!txtr->img)
	{
		err_msg = ft_strjoin("failed to load texture '", filename);
		tmp = err_msg;
		err_msg = ft_strjoin(err_msg, "'");
		free(tmp);
		print_error(err_msg);
		free(err_msg);
		return (1);
	}
	txtr->data = mlx_get_data_addr(txtr->img, &v->bpp, &txtr->size_line, &v->endian);
	return (0);
}

int	init_txtr(t_var *v)
{
	if (load_txtr(v, "textures/wood.xpm", &v->txtr[NO])
		|| load_txtr(v, "textures/greystone.xpm", &v->txtr[SO])
		|| load_txtr(v, "textures/purplestone.xpm", &v->txtr[EA])
		|| load_txtr(v, "textures/redbrick.xpm", &v->txtr[WE]))
		return (1);
	return (0);
}

int	init_game(t_var *v)
{
	v->mlx = mlx_init();
	if (!v->mlx)
	{
		print_error("mlx failure");
		return (1);
	}
	v->win = mlx_new_window(v->mlx, W, H, "cub3d");
	v->img = mlx_new_image(v->mlx, W, H);
	if (!v->win || !v->img)
	{
		print_error("mlx failure");
		return (1);
	}
	v->img_data = mlx_get_data_addr(v->img, &v->bpp, &v->size_line, &v->endian);
	init_key(&v->key);
	if (init_txtr(v))
		return (1);
	mlx_mouse_get_pos(v->win, &v->mouse_x, &v->mouse_y);
	v->old_mouse_x = v->mouse_x;
	v->redisplay = 1;
	v->t_last_frame = get_time();
	return (0);
}




