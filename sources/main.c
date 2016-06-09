/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/06/09 17:40:32 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		convert(t_var *v, int x, int y, int i)
{
	v->tab[v->p] = (int ***)malloc(sizeof(int **) * v->lns);
	while (v->s[i] != 0 && y < v->lns && (x = 0) == 0)
	{
		v->tab[v->p][y] = (int **)malloc(sizeof(int *) * v->wth);
		while (x < v->wth)
		{
			v->tab[v->p][y][x] = (int *)malloc(sizeof(int) * 3);
			v->tab[v->p][y][x][0] = x;
			v->tab[v->p][y][x][1] = y;
			v->tab[v->p][y][x++][2] = ft_atoi(v->s, &i, 0, 1);
			while (v->s[i] == 32)
				i++;
		}
		y++;
	}
}

static void		assign(t_var *v)
{
	v->fls[v->p] = v->fln;
	v->zmv[v->p] = 10;
	v->rtx[v->p] = 0;
	v->rty[v->p] = 0;
	v->rtz[v->p] = 0;
	v->clr[v->p] = OBJ_COLOR;
	v->dlr[v->p] = dark_color(v->clr[v->p], 0, 0, 0);
	convert(v, 0, 0, 0);
	v->mov[v->p] = (int *)malloc(sizeof(int) * 2);
	v->val[v->p] = (int *)malloc(sizeof(int) * 2);
	v->mov[v->p][0] = 0;
	v->mov[v->p][1] = 0;
	v->val[v->p][0] = v->lns;
	v->val[v->p][1] = v->wth;
	if (v->wth == 1)
		v->wth++;
	if (v->lns == 1)
		v->lns++;
	if (((WIN_W - 263) / (v->wth - 1)) <= ((WIN_H - 116) / (v->lns - 1)))
		v->zom[v->p] = (WIN_W - 263) / (v->wth - 1);
	else
		v->zom[v->p] = (WIN_H - 116) / (v->lns - 1);
}

static void		init_win(t_var *v)
{
	v->max = v->p;
	v->p = 0;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, -1, -1, WIN_W, WIN_H, "fdf - bsouchet");
	mlx_expose_hook(v->win, expose_hook, v);
	mlx_hook(v->win, 17, 0, close_hook, v);
	mlx_hook(v->win, 2, 0, key_hook, v);
	mlx_do_key_autorepeaton(v->mlx);
	mlx_loop(v->mlx);
	exit(0);
}

static void		execute(t_var *v, int fd)
{
	v->max = 0;
	while (++v->max < v->nbr && (v->fln = v->fls[v->max]) != NULL)
	{
		v->lns = 0;
		v->wth = -1;
		v->inv = 0;
		v->c = (char *)malloc(sizeof(char) * 2);
		v->s = (char *)malloc(sizeof(char) * 2);
		if ((fd = open(v->fls[v->max], O_RDONLY)) == -1)
			ft_pr(v, 3);
		while (fd != -1 && GNL(fd, &v->c, v) > 0 && (v = check(v, 0))->lns > -1)
			v->s = ft_strjoin2(ft_strjoin2(v->s, " ", 0), v->c, 2);
		if (fd != -1 && v->wth == -2)
			ft_pr(v, 8);
		else if (fd != -1 && v->wth == 0)
			ft_pr(v, 5);
		else if (fd != -1 && v->inv == 0 && ++v->p > -5)
			assign(v);
		if (fd != -1 && close(fd) == -1)
			ft_pr(v, 3);
		free(v->c);
		free(v->s);
	}
	if (fd != -1 && v->p != -1)
		init_win(v);
}

int				main(int ac, char **av)
{
	t_var	*v;

	v = (t_var *)malloc(sizeof(t_var) * 1);
	v->nbr = ac;
	v->fls = av;
	if (!(v->tab = (int ****)malloc(sizeof(int ***) * (v->nbr - 1))) ||
		!(v->val = (int **)malloc(sizeof(int *) * (v->nbr - 1))) ||
		!(v->mov = (int **)malloc(sizeof(int *) * (v->nbr - 1))) ||
		!(v->dlr = (int *)malloc(sizeof(int) * (v->nbr - 1))) ||
		!(v->rtx = (int *)malloc(sizeof(int) * (v->nbr - 1))) ||
		!(v->rty = (int *)malloc(sizeof(int) * (v->nbr - 1))) ||
		!(v->rtz = (int *)malloc(sizeof(int) * (v->nbr - 1))) ||
		!(v->zmv = (int *)malloc(sizeof(int) * (v->nbr - 1))) ||
		!(v->zom = (int *)malloc(sizeof(int) * (v->nbr - 1))) ||
		!(v->clr = (int *)malloc(sizeof(int) * (v->nbr - 1))))
		return (ft_pr(v, 9));
	if (ac < 2)
		return (ft_pr(v, 1));
	else if (BUFF_SIZE < 1)
		return (ft_pr(v, 2));
	else if (WIN_W < 1024 || WIN_H < 576)
		return (ft_pr(v, 0));
	else if ((v->p = -1) < 0)
		execute(v, 0);
	return (0);
}
