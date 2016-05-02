/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 15:39:40 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/02 16:43:12 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		rand_color(int r, int g, int b)
{
	while (42)
	{
		if ((r <= MIN_V && g <= MIN_V) || (r <= MIN_V && b <= MIN_V) ||
			(g <= MIN_V && b <= MIN_V))
		{
			r = ft_rand(0, 255);
			g = ft_rand(0, 255);
			b = ft_rand(0, 255);
		}
		else
			return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
	}
	return (0);
}

int		face_color(t_var *v)
{
	int num;

	num = v->rty[v->p];
	while (num < 0)
		num += 360;
	while (num >= 360)
		num -= 360;
	if ((num >= 0 && num < 90) || (num >= 270 && num < 360))
		return (v->clr[v->p]);
	return (v->dlr[v->p]);
}

t_var	*rotate_point(t_var *v, int x, int y, int p)
{
	int x_new;
	int y_new;
	int	z_new;

	x_new = (((float)(int)((cos(v->rtz[v->p] * (PI / 180.0))) * 10000000)) /
	10000000) * (v->tab[v->p][y][x][0] - (213 + ((WIN_W - 213) / 2))) -
	(((float)(int)((sin(v->rtz[v->p] * (PI / 180.0))) * 10000000)) / 10000000) *
	(v->tab[v->p][y][x][1] - (25 + ((WIN_H - 116) / 2))) +
	(213 + ((WIN_W - 213) / 2));
	y_new = (((float)(int)((sin(v->rtz[v->p] * (PI / 180.0))) * 10000000)) /
	10000000) * (v->tab[v->p][y][x][0] - (213 + ((WIN_W - 213) / 2))) +
	(((float)(int)((cos(v->rtz[v->p] * (PI / 180.0))) * 10000000)) / 10000000) *
	(v->tab[v->p][y][x][1] - (25 + ((WIN_H - 116) / 2))) +
	(25 + ((WIN_H - 116) / 2));
	v->tab[v->p][y][x][1] = (cos(v->rtx[v->p] * (PI / 180.0)) * (y_new - (25 +
	((WIN_H - 116) / 2)))) - (sin(v->rtx[v->p] * (PI / 180.0)) *
	(-(v->tab[v->p][y][x][2] * (p / 2)) - 0)) + (25 + ((WIN_H - 116) / 2));
	z_new = (sin(v->rtx[v->p] * (PI / 180.0)) *
	(y_new - (25 + ((WIN_H - 116) / 2)))) + (cos(v->rtx[v->p] * (PI / 180.0)) *
	(-(v->tab[v->p][y][x][2] * (p / 2)) - 0));
	v->tab[v->p][y][x][0] = sin(v->rty[v->p] * (PI / 180.0)) *
	(z_new) + cos(v->rty[v->p] * (PI / 180.0)) * (x_new - (213 + ((WIN_W - 213)
	/ 2))) + (213 + ((WIN_W - 213) / 2));
	return (v);
}

t_var	*init_tab(t_var *v, int y, int x)
{
	int x_off;
	int y_off;

	x_off = 238 + ((WIN_W - (v->zom[v->p] * (v->val[v->p][1] - 1)) - 263) / 2);
	y_off = 25 + ((WIN_H - (v->zom[v->p] * (v->val[v->p][0] - 1)) - 116) / 2);
	while (y < v->val[v->p][0] && (x = 0) < 1)
	{
		while (x < v->val[v->p][1])
		{
			v->tab[v->p][y][x][0] = x_off + (x * v->zom[v->p]);
			v->tab[v->p][y][x][1] = y_off + (y * v->zom[v->p]);
			v = rotate_point(v, x, y, v->zom[v->p]);
			x++;
		}
		y++;
	}
	return (v);
}

t_var	*reset_tab(t_var *v)
{
	int lns;
	int wth;

	lns = (v->val[v->p][0] != 1) ? v->val[v->p][0] : 2;
	wth = (v->val[v->p][1] != 1) ? v->val[v->p][1] : 2;
	v = init_tab(v, 0, 0);
	v->mov[v->p][1] = 0;
	v->clr[v->p] = OBJ_COLOR;
	v->dlr[v->p] = dark_color(v->clr[v->p], 0, 0, 0);
	v->zmv[v->p] = 10;
	v->rtx[v->p] = 0;
	v->rty[v->p] = 0;
	v->rtz[v->p] = 0;
	if (((WIN_W - 263) / (wth - 1)) <= ((WIN_H - 116) / (lns - 1)))
		v->zom[v->p] = (WIN_W - 263) / (wth - 1);
	else
		v->zom[v->p] = (WIN_H - 116) / (lns - 1);
	return (v);
}
