/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/04/12 17:36:20 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		***convert(t_var v, int x, int y, int i)
{
	if (!(v.tab[v.p] = (int ***)malloc(sizeof(int **) * v.lns)) &&
		ft_pr(v, 9) < 0)
		return (NULL);
	while (v.s[i] != 0 && y < v.lns && (x = 0) == 0)
	{
		if (!(v.tab[v.p][y] = (int **)malloc(sizeof(int *) * v.wth)) &&
			ft_pr(v, 9) < 0)
			return (NULL);
		while (x < v.wth)
		{
			if (!(v.tab[v.p][y][x] = (int *)malloc(sizeof(int) * 3)) &&
				ft_pr(v, 9) < 0)
				return (NULL);
			v.tab[v.p][y][x][0] = x;
			v.tab[v.p][y][x][1] = y;
			v.tab[v.p][y][x++][2] = ft_atoi(v.s, &i, 0, 1);
			while (v.s[i] == 32)
				i++;
		}
		y++;
	}
	return (v.tab[v.p]);
}

static t_var	assign(t_var v)
{
	v.fls[v.p] = v.fln;
	v.zmv[v.p] = 10;
	v.rtx[v.p] = 0;
	v.rty[v.p] = 0;
	v.rtz[v.p] = 0;
	v.clr[v.p] = OBJ_COLOR;
	v.dlr[v.p] = dark_color(v.clr[v.p], 0, 0, 0);
	v.tab[v.p] = convert(v, 0, 0, 0);
	if (((WIN_W - 263) / (v.wth - 1)) <= ((WIN_H - 116) / (v.lns - 1)))
		v.zom[v.p] = (WIN_W - 263) / (v.wth - 1);
	else
		v.zom[v.p] = (WIN_H - 116) / (v.lns - 1);
	v.mov[v.p] = (int *)malloc(sizeof(int) * 2);
	v.val[v.p] = (int *)malloc(sizeof(int) * 2);
	v.mov[v.p][0] = 0;
	v.mov[v.p][1] = 0;
	v.val[v.p][0] = v.lns;
	v.val[v.p][1] = v.wth;
	return (v);
}

static int		init_win(t_var v)
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

static int		execute(t_var v, int fd)
{
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
	if (v.p != -1)
		init_win(v);
	return (0);
}

int				main(int ac, char **av)
{
	t_var	v;

	v.nbr = ac;
	v.fls = av;
	v.max = 0;
	if (!(v.tab = (int ****)malloc(sizeof(int ***) * (v.nbr - 1))) ||
		!(v.val = (int **)malloc(sizeof(int *) * (v.nbr - 1))) ||
		!(v.mov = (int **)malloc(sizeof(int *) * (v.nbr - 1))) ||
		!(v.dlr = (int *)malloc(sizeof(int) * (v.nbr - 1))) ||
		!(v.rtx = (int *)malloc(sizeof(int) * (v.nbr - 1))) ||
		!(v.rty = (int *)malloc(sizeof(int) * (v.nbr - 1))) ||
		!(v.rtz = (int *)malloc(sizeof(int) * (v.nbr - 1))) ||
		!(v.zmv = (int *)malloc(sizeof(int) * (v.nbr - 1))) ||
		!(v.zom = (int *)malloc(sizeof(int) * (v.nbr - 1))) ||
		!(v.clr = (int *)malloc(sizeof(int) * (v.nbr - 1))))
		return (ft_pr(v, 9));
	if (ac < 2)
		return (ft_pr(v, 1));
	else if (BUFF_SIZE < 1)
		return (ft_pr(v, 2));
	else if (WIN_W < 1024 || WIN_H < 576)
		return (ft_pr(v, 0));
	else if ((v.p = -1) < 0)
		execute(v, 0);
	return (0);
}
