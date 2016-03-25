/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 08:51:06 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/25 15:26:20 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		expose_hook(t_var *v)
{
	int tmp;
	int	tmp2;

	v->img = mlx_new_image(v->mlx, WIN_W, WIN_H);
	v->d = mlx_get_data_addr(v->img, &v->bpp, &v->sl, &v->end);
	tmp = 238 + ((WIN_W - (v->zom[v->p] * (v->val[v->p][1] - 1)) - 263) / 2);
	tmp2 = 25 + ((WIN_H - (v->zom[v->p] * (v->val[v->p][0] - 1)) - 116) / 2);
	v->nam = ft_strjoin("File : ", v->fls[v->p]);
	v->lgr = ft_strjoin(
		"Edges : ", ft_itoa((((v->val[v->p][0] - 1) * v->val[v->p][1]) * 2)));
	v->len = WIN_W - 50 - ft_strlen(ft_strjoin("File : ", v->fls[v->p])) * 10;
	v = user_interface(v);
	v->y = tmp2;
	while (v->y - tmp2 <= (v->zom[v->p] * (v->val[v->p][0] - 1)))
	{
		v->x = tmp;
		while (v->x <= (v->zom[v->p] * (v->val[v->p][1] - 1) + tmp)
		&& put_pixel(v, OBJ_COLOR) == 0)
			v->x++;
		v->y = v->y + (v->zom[v->p]);
	}
	v->y = tmp2;
	while (v->y - tmp2 <= (v->zom[v->p] * (v->val[v->p][0] - 1)))
	{
		v->x = tmp;
		while (v->x - tmp <= (v->zom[v->p] * (v->val[v->p][1] - 1))
		&& put_pixel(v, OBJ_COLOR) == 0)
			v->x = v->x + (v->zom[v->p]);
		v->y++;
	}
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	user_interface_texts(v);
	return (0);
}

int		key_hook(int keycode, t_var *v)
{
	if (keycode == 53)
	{
		mlx_destroy_image(v->mlx, v->img);
		mlx_destroy_window(v->mlx, v->win);
		exit(0);
	}
	else if (keycode == 71)
	{
		if (((WIN_W - 263) / (v->val[v->p][0] - 1)) <=
		((WIN_H - 116) / (v->val[v->p][1] - 1)))
			v->zom[v->p] = (WIN_W - 263) / (v->val[v->p][0] - 1);
		else
			v->zom[v->p] = (WIN_H - 116) / (v->val[v->p][1] - 1);
		mlx_destroy_image(v->mlx, v->img);
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	else if (keycode == 69)
	{
		v->zom[v->p] += (v->zom[v->p] / 4) + 1;
		mlx_destroy_image(v->mlx, v->img);
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	else if (keycode == 78)
	{
		if (v->zom[v->p] > 1)
			v->zom[v->p] -= (v->zom[v->p] / 4) + 1;
		mlx_destroy_image(v->mlx, v->img);
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	else if (keycode == 116 && v->p > 0 && v->p-- > -5)
	{
		mlx_destroy_image(v->mlx, v->img);
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	else if (keycode == 121 && v->p < v->max && v->p++ > -5)
	{
		mlx_destroy_image(v->mlx, v->img);
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
