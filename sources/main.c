/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/23 16:28:57 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static int		**convert(t_var v, int x, int y, int i)
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

static t_var	assign(t_var v, int type)
{
	if (type == 0 && (v.p = -1) == -1)
		v.max = 0;
	else if (type == 1 && (v.lns = 0) > -1)
	{
		v.wth = -1;
		v.inv = 0;
		v.c = ft_strnew(1);
		v.s = ft_strnew(1);
	}
	else if (type == 2 && (v.fls[v.p] = v.fln) != NULL)
	{
		v.tab[v.p] = convert(v, 0, 0, 0);
		if (((WIN_W - 263) / (v.wth - 1)) <= ((WIN_H - 116) / (v.lns - 1)))
			v.zom[v.p] = (WIN_W - 263) / (v.wth - 1);
		else
			v.zom[v.p] = (WIN_H - 116) / (v.lns - 1);
		v.val[v.p] = (int *)malloc(sizeof(int) * 2);
		v.val[v.p][0] = v.lns;
		v.val[v.p][1] = v.wth;
	}
	return (v);
}

static int		execute(t_var v, int fd)
{
	while (++v.max < v.nbr && (v.fln = v.fls[v.max]) != NULL)
	{
		v = assign(v, 1);
		if ((fd = open(v.fls[v.max], O_RDONLY)) == -1)
			ft_pr(v, 3);
		while (get_next_line(fd, &v.c, v) > 0 && (v = check(v, 0)).lns > -1)
			v.s = ft_strjoin(ft_strjoin(v.s, " "), v.c);
		if (v.wth == -2)
			ft_pr(v, 8);
		else if (v.wth == 0)
			ft_pr(v, 5);
		else if (v.inv == 0 && ++v.p > -5)
			v = assign(v, 2);
		if (close(fd) == -1)
			ft_pr(v, 3);
	}
	init_window(v);
	return (0);
}

int				main(int ac, char **av)
{
	t_var	v;

	v.nbr = ac;
	v.fls = av;
	v = assign(v, 0);
	if (!(v.tab = (int ***)malloc(sizeof(int **) * (v.nbr - 1))) ||
		!(v.val = (int **)malloc(sizeof(int *) * (v.nbr - 1))) ||
		!(v.zom = (int *)malloc(sizeof(int) * (v.nbr - 1))))
		return (ft_pr(v, 9));
	if (ac < 2)
		return (ft_pr(v, 1));
	else if (BUFF_SIZE < 1)
		return (ft_pr(v, 2));
	else if (WIN_W < 1024 || WIN_H < 576)
		return (ft_pr(v, 0));
	else
		execute(v, 0);
	return (0);
}
