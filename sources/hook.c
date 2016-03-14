/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 08:51:06 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/14 17:17:58 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		expose_hook(t_var *v)
{
	int tmp;

	tmp = 213 + ((WIN_W - (v->zom[v->p] * v->val[v->p][1]) - 238) / 2);
	v->nam = ft_strjoin("File : ", v->fls[v->p]);
	v->lgr = ft_strjoin(
			"Edges : ", ft_itoa((((v->val[v->p][0] - 1) * v->val[v->p][1]) * 2)));
	v->len = WIN_W - 50 - ft_strlen(ft_strjoin("File : ", v->fls[v->p])) * 10;
	v->y = 0;

	while (v->y <= WIN_H)
	{
		v->x = 0;
		while (v->x <= WIN_W)
			mlx_pixel_put(v->mlx, v->win, v->x++, v->y, BG2_COLOR);
		v->y++;
	}

	v->y = 0;

	while (v->y <= WIN_H)
	{
		v->x = 0;
		while (v->x <= 213)
			mlx_pixel_put(v->mlx, v->win, v->x++, v->y, BG_COLOR);
		v->y++;
	}

	v->y = 25;
	/*while (v->y - 25 < (v->zom[v->p] * v->val[v->p][0]))
	{
		v->x = tmp;
		while (v->x - tmp < (v->zom[v->p] * v->val[v->p][1]))
			mlx_pixel_put(v->mlx, v->win, v->x++, v->y, BG_COLOR);
		v->y++;
	}*/
	v->x = 25;
	v->y = 25;
	mlx_draw(v, 188, 153);
	v->x = 25;
	v->y = 178;
	mlx_draw(v, 188, 266);
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
	v->y = (WIN_H - 65);
	mlx_draw(v, 188, (WIN_H - 25));
	mlx_string_put(v->mlx, v->win, 37, (WIN_H - 55), UI_COLOR, v->lgr);
	v->x = v->len - 1;
	mlx_draw(v, (WIN_W - 25), (WIN_H - 25));
	mlx_string_put(v->mlx, v->win, v->len + 11, (WIN_H - 55), UI_COLOR, v->nam);
	return (0);
}



int		key_hook(int keycode, t_var *v)
{
	if (keycode == 53)
	{
		mlx_destroy_window(v->mlx, v->win);
		exit(0);
		return (0);
	}
	else if (keycode == 116 && v->p > 0 && v->p-- > -5)
	{
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	else if (keycode == 121 && v->p < v->max && v->p++ > -5)
	{
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	return (0);
}

int		close_hook(int button, t_var *v)
{
	(void)button;
	(void)v;
	exit(0);
	return (0);
}
