/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 08:59:37 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/14 10:19:55 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_draw(t_var *v, int x, int y)
{
	int tmp1;
	int tmp2;

	tmp1 = v->x;
	tmp2 = v->y;
	while (v->x <= x)
		mlx_pixel_put(v->mlx, v->win, v->x++, v->y, UI_COLOR);
	while (v->y <= y)
		mlx_pixel_put(v->mlx, v->win, v->x, v->y++, UI_COLOR);
	while (v->x >= tmp1)
		mlx_pixel_put(v->mlx, v->win, v->x--, v->y, UI_COLOR);
	while (v->y >= tmp2)
		mlx_pixel_put(v->mlx, v->win, v->x, v->y--, UI_COLOR);
}

int		init_window(t_var *v)
{
	v->max = v->p;
	v->p = 0;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIN_W, WIN_H, "fdf - bsouchet");
	mlx_expose_hook(v->win, expose_hook, v);
	mlx_hook(v->win, 17, 0, close_hook, v);
	mlx_hook(v->win, 2, 0, key_hook, v);
	mlx_do_key_autorepeaton(v->mlx);
	mlx_loop(v->mlx);
	exit(0);
	return (0);
}
