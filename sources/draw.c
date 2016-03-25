/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 08:59:37 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/25 13:21:16 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		put_pixel(t_var *v, int color)
{
	int		i;
	char	*rgb;

	if  (v->x >= 0 && v->x <= WIN_W && v->y >= 0 && v->y <= WIN_H)
	{
		i = ((int)v->x * (v->bpp / 8)) + ((int)v->y * v->sl);
		rgb = (char*)&color;
		v->d[i] = rgb[0];
		v->d[++i] = rgb[1];
		v->d[++i] = rgb[2];
	}
	return (0);
}

t_var	*user_interface(t_var *v)
{
	v->y = 0;
	while (v->y < WIN_H)
	{
		v->x = 0;
		while (v->x <= 213 && put_pixel(v, BG_COLOR) == 0)
			v->x++;
		while (v->x < WIN_W && put_pixel(v, BG2_COLOR) == 0)
			v->x++;
		v->y++;
	}
	v->x = 25;
	v->y = 25;
	mlx_draw(v, 188, 153);
	v->x = 25;
	v->y = 178;
	mlx_draw(v, 188, 266);
	v->y = (WIN_H - 65);
	mlx_draw(v, 188, (WIN_H - 25));
	v->x = v->len - 1;
	mlx_draw(v, (WIN_W - 25), (WIN_H - 25));
	return (v);
}

void	user_interface_texts(t_var *v)
{
	mlx_string_put(v->mlx, v->win, 41, 35, UI_COLOR, "Controls Keys");
	mlx_string_put(v->mlx, v->win, 37, 63, UI_COLOR, "Quit = ESC");
	mlx_string_put(v->mlx, v->win, 37, 83, UI_COLOR, "Move = ^ v < >");
	mlx_string_put(v->mlx, v->win, 37, 103, UI_COLOR, "Zoom = + or -");
	mlx_string_put(v->mlx, v->win, 37, 123, UI_COLOR, "Rot8 = W S A D");
	mlx_string_put(v->mlx, v->win, 37, 188, UI_COLOR, "Files Explorer");
	if (v->p > 0)
		mlx_string_put(v->mlx, v->win, 37, 216, UI_COLOR, "Prev = PAGE UP");
	else
		mlx_string_put(v->mlx, v->win, 37, 216, UI2_COLOR, "Prev = PAGE UP");
	if (v->p < v->max)
		mlx_string_put(v->mlx, v->win, 37, 236, UI_COLOR, "Next = PAGE DW");
	else
		mlx_string_put(v->mlx, v->win, 37, 236, UI2_COLOR, "Next = PAGE DW");
	mlx_string_put(v->mlx, v->win, 37, (WIN_H - 55), UI_COLOR, v->lgr);
	mlx_string_put(v->mlx, v->win, v->len + 11, (WIN_H - 55), UI_COLOR, v->nam);
}

void	mlx_draw(t_var *v, int x, int y)
{
	int tmp1;
	int tmp2;

	tmp1 = v->x;
	tmp2 = v->y;
	while (v->x <= x && put_pixel(v, UI_COLOR) == 0)
		v->x++;
	while (v->y <= y && put_pixel(v, UI_COLOR) == 0)
		v->y++;
	while (v->x >= tmp1 && put_pixel(v, UI_COLOR) == 0)
		v->x--;
	while (v->y >= tmp2 && put_pixel(v, UI_COLOR) == 0)
		v->y--;
}

int		init_window(t_var v)
{
	v.max = v.p;
	v.p = 0;
	v.mlx = mlx_init();
	v.img = mlx_new_image(v.mlx, WIN_W, WIN_H);
	v.win = mlx_new_window(v.mlx, -1, -1, WIN_W, WIN_H, "fdf - bsouchet");
	v.d = mlx_get_data_addr(v.img, &v.bpp, &v.sl, &v.end);
	mlx_expose_hook(v.win, expose_hook, &v);
	mlx_hook(v.win, 17, 0, close_hook, &v);
	mlx_hook(v.win, 2, 0, key_hook, &v);
	mlx_do_key_autorepeaton(v.mlx);
	mlx_loop(v.mlx);
	exit(0);
	return (0);
}
