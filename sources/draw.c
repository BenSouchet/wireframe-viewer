/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 08:59:37 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/12 17:06:10 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		put_pixel(t_var *v, int color, int type)
{
	int		i;
	int		x;
	int		y;
	char	*rgb;

	x = v->x;
	y = v->y;
	if (type == 1)
	{
		x = v->tab[v->p][v->y][v->x][0] + v->mov[v->p][0];
		y = v->tab[v->p][v->y][v->x][1] + v->mov[v->p][1];
	}
	if (((type == 1 && x > 213) || (type != 1 && x >= 0))
	&& x < WIN_W && y >= 0 && y < WIN_H)
	{
		i = ((int)v->x * (v->bpp / 8)) + ((int)v->y * v->sl);
		rgb = (char*)&color;
		v->d[i] = rgb[0];
		v->d[++i] = rgb[1];
		v->d[++i] = rgb[2];
	}
	return (0);
}

void	draw_line(t_var *v, int x, int y, int type)
{
	double	tx;
	double	dist_x;
	double	dist_y;

	tx = 0.0;
	dist_x = v->tab[v->p][y][x + 1][0] - v->tab[v->p][y][x][0];
	dist_y = v->tab[v->p][y][x + 1][1] - v->tab[v->p][y][x][1];
	if (type == 1)
	{
		dist_x = v->tab[v->p][y + 1][x][0] - v->tab[v->p][y][x][0];
		dist_y = v->tab[v->p][y + 1][x][1] - v->tab[v->p][y][x][1];
	}
	while (tx <= 1)
	{
		v->x = v->tab[v->p][y][x][0] + (dist_x * tx) + v->mov[v->p][0];
		v->y = v->tab[v->p][y][x][1] + (dist_y * tx) + v->mov[v->p][1];
		put_pixel(v, face_color(v), 0);
		tx += 1. / sqrt((dist_x * dist_x) + (dist_y * dist_y));
	}
}

t_var	*user_interface(t_var *v, int type)
{
	v->y = -1;
	if (type == 1)
		while (++v->y < WIN_H && (v->x = 214) > -1)
			while (v->x < WIN_W && put_pixel(v, BG2_COLOR, 0) == 0)
				v->x++;
	else if (type == 2)
	{
		while (++v->y < WIN_H && (v->x = 0) > -1)
			while (v->x <= 213 && put_pixel(v, BG_COLOR, 0) == 0)
				v->x++;
		v->nam = ft_strjoin("File : ", v->fls[v->p]);
		v->len = WIN_W - 50 - ft_strlen(v->nam) * 10;
		v->x = 25;
		v->y = 25;
		mlx_draw(v, 188, 173);
		v->x = 25;
		v->y = 197;
		mlx_draw(v, 188, 286);
		v->y = (WIN_H - 65);
		mlx_draw(v, 188, (WIN_H - 25));
		v->x = v->len - 1;
		mlx_draw(v, (WIN_W - 25), (WIN_H - 25));
	}
	return (v);
}

void	user_interface_texts(t_var *v)
{
	v = check_edges(v);
	mlx_string_put(v->mlx, v->win, 41, 35, UI_COLOR, "Controls Keys");
	mlx_string_put(v->mlx, v->win, 37, 63, UI_COLOR, "Move = ^ v < >");
	mlx_string_put(v->mlx, v->win, 37, 83, UI_COLOR, "Zoom = + or -");
	mlx_string_put(v->mlx, v->win, 37, 103, UI_COLOR, "Rot8 = W S A D");
	mlx_string_put(v->mlx, v->win, 37, 123, UI_COLOR, "Color = SHIFT");
	mlx_string_put(v->mlx, v->win, 37, 143, UI_COLOR, "Reset = CLEAR");
	mlx_string_put(v->mlx, v->win, 37, 208, UI_COLOR, "Files Explorer");
	if (v->p > 0)
		mlx_string_put(v->mlx, v->win, 37, 236, UI_COLOR, "Prev = PAGE UP");
	else
		mlx_string_put(v->mlx, v->win, 37, 236, UI2_COLOR, "Prev = PAGE UP");
	if (v->p < v->max)
		mlx_string_put(v->mlx, v->win, 37, 256, UI_COLOR, "Next = PAGE DW");
	else
		mlx_string_put(v->mlx, v->win, 37, 256, UI2_COLOR, "Next = PAGE DW");
	mlx_string_put(v->mlx, v->win, 37, (WIN_H - 55), UI_COLOR, v->lgr);
	free(v->lgr);
	mlx_string_put(v->mlx, v->win, v->len + 11, (WIN_H - 55), UI_COLOR, v->nam);
	free(v->nam);
}

void	mlx_draw(t_var *v, int x, int y)
{
	int tmp1;
	int tmp2;

	tmp1 = v->x;
	tmp2 = v->y;
	while (v->x <= x && put_pixel(v, UI_COLOR, 0) == 0)
		v->x++;
	while (v->y <= y && put_pixel(v, UI_COLOR, 0) == 0)
		v->y++;
	while (v->x >= tmp1 && put_pixel(v, UI_COLOR, 0) == 0)
		v->x--;
	while (v->y >= tmp2 && put_pixel(v, UI_COLOR, 0) == 0)
		v->y--;
}
