/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 08:51:06 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/12 17:08:57 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				expose_hook(t_var *v)
{
	int	x;
	int	y;

	y = -1;
	v->img = mlx_new_image(v->mlx, WIN_W, WIN_H);
	v->d = mlx_get_data_addr(v->img, &v->bpp, &v->sl, &v->end);
	v = init_tab(v, 0, 0);
	v = user_interface(v, 1);
	while (++y < v->val[v->p][0] && (x = -1) < 0)
		while (++x < (v->val[v->p][1] - 1))
			draw_line(v, x, y, 0);
	y = -1;
	while (++y < (v->val[v->p][0] - 1) && (x = -1) < 0)
		while (++x < v->val[v->p][1])
			draw_line(v, x, y, 1);
	v = user_interface(v, 2);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	user_interface_texts(v);
	return (0);
}

static t_var	*key_hook_rotate(t_var *v, int keycode)
{
	if (keycode == 0)
		v->rty[v->p] -= 5;
	else if (keycode == 1)
		v->rtx[v->p] += 5;
	else if (keycode == 2)
		v->rty[v->p] += 5;
	else if (keycode == 12)
		v->rtz[v->p] -= 5;
	else if (keycode == 13)
		v->rtx[v->p] -= 5;
	else if (keycode == 14)
		v->rtz[v->p] += 5;
	else if (keycode == 69 && (v->zmv[v->p] += (v->zmv[v->p] / 4) + 1) > 0)
		v->zom[v->p] += (v->zom[v->p] / 4) + 1;
	else if (keycode == 71 && (v->mov[v->p][0] = 0) > -1)
		v = reset_tab(v);
	else if (keycode == 78 && v->zom[v->p] > 1)
	{
		if (v->zmv[v->p] > 10)
			v->zmv[v->p] -= (v->zmv[v->p] / 4) + 1;
		v->zom[v->p] -= (v->zom[v->p] / 4) + 1;
	}
	return (v);
}

static t_var	*key_hook_translate(t_var *v, int keycode)
{
	if (keycode == 116 && v->p > 0)
		v->p--;
	else if (keycode == 121 && v->p < v->max)
		v->p++;
	else if (keycode == 123)
		v->mov[v->p][0] -= v->zmv[v->p];
	else if (keycode == 124)
		v->mov[v->p][0] += v->zmv[v->p];
	else if (keycode == 126)
		v->mov[v->p][1] -= v->zmv[v->p];
	else if (keycode == 125)
		v->mov[v->p][1] += v->zmv[v->p];
	else if (keycode == 257 || keycode == 258)
	{
		v->clr[v->p] = rand_color(0, 0, 0);
		v->dlr[v->p] = dark_color(v->clr[v->p], 0, 0, 0);
	}
	return (v);
}

int				key_hook(int keycode, t_var *v)
{
	if (keycode == 53)
	{
		mlx_destroy_image(v->mlx, v->img);
		mlx_destroy_window(v->mlx, v->win);
		exit(0);
	}
	else
	{
		if (keycode >= 0 && keycode < 80)
			v = key_hook_rotate(v, keycode);
		else if (keycode > 110 && keycode < 260)
			v = key_hook_translate(v, keycode);
		mlx_destroy_image(v->mlx, v->img);
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	return (0);
}

int				close_hook(int button, t_var *v)
{
	(void)button;
	(void)v;
	exit(0);
	return (0);
}
