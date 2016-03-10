/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/10 16:11:40 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>

static int		ft_check_hex(char *s, int x, int *e, t_var v)
{
	int letter;
	int num;
	int i;

	i = 0;
	num = 0;
	letter = -1;
	while (x++ > -1 && num++ > -1 && s[x] != 32 && s[x] != 0)
		if ((s[x] < 48 || s[x] > 57) && (s[x] < 65 || s[x] > 70) && (*e)++ == 0)
			ft_pr(v, 6);
		else if ((letter == -1 || s[x] == letter) && i++ > -1)
			letter = s[x];
		else if (s[x] != letter)
			i = 0;
	if (((num == 4 && i != 3) || (num != 4 && num != 7)) && (*e)++ == 0)
		ft_pr(v, 6);
	return (1);
}

static t_var	ft_check_number(t_var v, int e)
{
	if (v.c[v.x] == 43 || v.c[v.x] == 45)
		while (v.x++ > -1 && v.c[v.x] != 32 && v.c[v.x] != 0 && v.c[v.x] != 44)
			if (e == 0 && (v.c[v.x] < 48 || v.c[v.x] > 57) && ft_pr(v, 7) < 0)
				e++;
	v.x--;
	while (v.x++ > -5 && v.c[v.x] != 32 && v.c[v.x] != 0 && v.c[v.x] != 44)
		if (e == 0 && (v.c[v.x] < 48 || v.c[v.x] > 57) && ft_pr(v, 4) < 0)
			e++;
	if (v.c[v.x] == 44 && v.c[v.x + 1] == 48 && v.c[v.x + 2] == 120
			&& ft_check_hex(v.c, v.x + 2, &e, v) > 0)
		while (v.x++ > -1 && v.c[v.x] != 32 && v.c[v.x] != 0)
			;
	else if (v.c[v.x] == 44)
	{
		if (e++ == 0)
			ft_pr(v, 4);
		while (v.x++ > -1 && v.c[v.x] != 32 && v.c[v.x] != 0)
			;
	}
	if (e != 0)
		v.inv = e;
	return (v);
}

static t_var	check(t_var v, int num)
{
	v.lns++;
	v.x = 0;
	while (v.c[v.x] != 0)
	{
		while (v.c[v.x] == 32)
			v.x++;
		if (v.c[v.x] != 32 && v.c[v.x] != 0 && num++ > -1)
			v = ft_check_number(v, 0);
	}
	if (v.wth == -1)
		v.wth = num;
	else if (v.wth != -1 && num != v.wth)
		v.wth = -2;
	return (v);
}

int				ft_atoi(char *str, int *k, int r, int s)
{
	while (str[*k] == 32)
		(*k)++;
	if (str[*k] == 45)
		s = -1;
	if (str[*k] == 43 || str[*k] == 45)
		(*k)++;
	while (str[*k] && str[*k] >= 48 && str[*k] <= 57)
	{
		r = r * 10 + str[*k] - 48;
		(*k)++;
	}
	while (str[*k] != 32 && str[*k] != 0)
		(*k)++;
	return (s * r);
}

static int		**ft_convert(t_var v, int x, int y, int i)
{
	if (!(v.tab[v.p] = (int **)malloc(sizeof(int *) * v.lns))
	&& ft_pr(v, 9) == -1)
		return (NULL);
	while (v.s[i] != 0 && y < v.lns && (x = 0) == 0)
	{
		if (!(v.tab[v.p][y] = (int *)malloc(sizeof(int) * v.wth))
		&& ft_pr(v, 9) < 0)
			return (NULL);
		while (x < v.wth)
		{
			v.tab[v.p][y][x++] = ft_atoi(v.s, &i, 0, 1);
			while (v.s[i] == 32)
				i++;
		}
		y++;
	}
	return (v.tab[v.p]);
}

void			mlx_draw_rectangle(t_var *v, int x, int y)
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

int				expose_hook(t_var *v)
{
	v->nam = ft_strjoin("File : ", v->fls[v->p]);
	v->lgr = ft_strjoin(
		"Edges : ", ft_itoa((((v->val[v->p][0] - 1) * v->val[v->p][1]) * 2)));
	v->len = WIN_W - 50 - ft_strlen(ft_strjoin("File : ", v->fls[v->p])) * 10;
	/*v->y = 0;
	while (v->y < WIN_H)
	{
		v->x = 0;
		while (v->x < WIN_W)
			mlx_pixel_put(v->mlx, v->win, v->x++, v->y, BG_COLOR);
		v->y++;
	}*/
	v->x = 25;
	v->y = 25;
	mlx_draw_rectangle(v, 188, 145);
	mlx_string_put(v->mlx, v->win, 37, 35, UI_COLOR, "Quit = ESC");
	mlx_string_put(v->mlx, v->win, 37, 55, UI_COLOR, "Move = ^ v < >");
	mlx_string_put(v->mlx, v->win, 37, 75, UI_COLOR, "Zoom = + or -");
	mlx_string_put(v->mlx, v->win, 37, 95, UI_COLOR, "Prev = L SHIFT");
	mlx_string_put(v->mlx, v->win, 37, 115, UI_COLOR, "Next = R SHIFT");
	v->y = (WIN_H - 65);
	mlx_draw_rectangle(v, 188, (WIN_H - 25));
	mlx_string_put(v->mlx, v->win, 37, (WIN_H - 55), UI_COLOR, v->lgr);
	v->x = v->len - 1;
	mlx_draw_rectangle(v, (WIN_W - 25), (WIN_H - 25));
	mlx_string_put(v->mlx, v->win, v->len + 11, (WIN_H - 55), UI_COLOR, v->nam);
	return (0);
}

int				key_hook(int keycode, t_var *v)
{
	if (keycode == 53)
	{
		mlx_destroy_window(v->mlx, v->win);
		exit(0);
	}
	else if (keycode == 257 && v->p > 0)
	{
		v->p--;
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	else if (keycode == 258 && v->p < v->max)
	{
		v->p++;
		mlx_clear_window(v->mlx, v->win);
		expose_hook(v);
	}
	return (0);
}

static int		close_hook(int button, t_var *v)
{
	(void)button;
	(void)v;
	exit(0);
	return (0);
}

static int		ft_draw(t_var v)
{
	v.max = v.p;
	v.p = 0;
	v.mlx = mlx_init();
	v.win = mlx_new_window(v.mlx, WIN_W, WIN_H, "fdf - bsouchet");
	mlx_expose_hook(v.win, &expose_hook, &v);
	mlx_key_hook(v.win, &key_hook, &v);
	mlx_hook(v.win, 17, 0, &close_hook, &v);
	mlx_loop(v.mlx);
	exit(0);
	return (0);
}

static t_var	assign(t_var v)
{
	v.fls[v.p] = v.fln;
	v.tab[v.p] = ft_convert(v, 0, 0, 0);
	v.val[v.p] = (int *)malloc(sizeof(int) * 2);
	v.val[v.p][0] = v.lns;
	v.val[v.p][1] = v.wth;
	return (v);
}

static int		execute(t_var v, int fd)
{
	if (!(v.tab = (int ***)malloc(sizeof(int **) * (v.nbr - 1))) ||
		!(v.val = (int **)malloc(sizeof(int *) * (v.nbr - 1))))
		return (ft_pr(v, 9));
	while (++v.max < v.nbr && (v.fln = v.fls[v.max]) != NULL)
	{
		v.lns = 0;
		v.wth = -1;
		v.inv = 0;
		v.c = ft_strnew(1);
		v.s = ft_strnew(1);
		if ((fd = open(v.fls[v.max], O_RDONLY)) == -1)
			ft_pr(v, 3);
		while (get_next_line(fd, &v.c, v) > 0 && (v = check(v, 0)).lns > -1)
			v.s = ft_strjoin(ft_strjoin(v.s, " "), v.c);
		if (v.wth == -2)
			ft_pr(v, 8);
		else if (v.wth == 0)
			ft_pr(v, 5);
		else if (v.inv == 0 && ++v.p > -5)
			v = assign(v);
		if (close(fd) == -1)
			ft_pr(v, 3);
	}
	ft_draw(v);
	return (0);
}

int				main(int ac, char **av)
{
	t_var	v;

	v.p = -1;
	v.max = 0;
	v.nbr = ac;
	v.fls = av;
	if (ac < 2)
		return (ft_pr(v, 1));
	else if (BUFF_SIZE < 1)
		return (ft_pr(v, 2));
	else
		execute(v, 0);
	return (0);
}
