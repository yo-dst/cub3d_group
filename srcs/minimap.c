#include "cub3d.h"

void    draw_minimap(t_var *v)
{
    int     i;
    int     j;
    double  coef_x;
    double  coef_y;
    double  radius;
    t_vec2  pixel_pos;

    i = -1;
    radius = 6;
    coef_x = radius * 2 / v->minimap.w;
    coef_y = radius * 2 / v->minimap.h;
    while (++i < v->minimap.h)
    {
        j = -1;
        while (++j < v->minimap.w)
        {
            pixel_pos = get_vec2(j * coef_x, i * coef_y);
            pixel_pos = add_vec2(get_vec2(v->player.x - radius, v->player.y - radius),
                pixel_pos);
            if (pixel_pos.x < 0 || pixel_pos.y < 0 || pixel_pos.x > v->map_w || pixel_pos.y > v->map_h)
                put_pixel(&v->minimap, j, i, GREEN_YELLOW);
            else if (pixel_pos.x - (int)pixel_pos.x <= 0.1 || pixel_pos.y - (int)pixel_pos.y <= 0.1)
                put_pixel(&v->minimap, j, i, 0x010101);
            else if (v->map[(int)pixel_pos.y][(int)pixel_pos.x] == WALL)
                put_pixel(&v->minimap, j, i, 0xA9A9A9);
            else
                put_pixel(&v->minimap, j, i, 0xFFFFFF);
        }
    }
    draw_line(&v->minimap, v->player.x, v->player.y, v->player_dir.x, v->player_dir.y);
    draw_circle(&v->minimap, v->minimap.w / 2, v->minimap.h / 2, 4, INDIAN_RED, 1);
    mlx_put_image_to_window(v->mlx, v->win, v->minimap.img, 0, 0);
}