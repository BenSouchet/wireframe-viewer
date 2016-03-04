/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/04 16:17:47 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		ft_check_hex(char *s, int x, int *e, t_data d)
{
	int letter;
	int num;
	int i;

	i = 0;
	num = 0;
	letter = -1;
	while (x++ > -1 && num++ > -1 && s[x] != 32 && s[x] != 0)
		if ((s[x] < 48 || s[x] > 57) && (s[x] < 65 || s[x] > 70) && (*e)++ == 0)
			ft_pr(d, 6);
		else if ((letter == -1 || s[x] == letter) && i++ > -1)
			letter = s[x];
		else if (s[x] != letter)
			i = 0;
	if (((num == 4 && i != 3) || (num != 4 && num != 7)) && (*e)++ == 0)
		ft_pr(d, 6);
	return (1);
}

static t_data	ft_check_number(t_data s, int e)
{
	if (s.c[s.x] == 43 || s.c[s.x] == 45)
		while (s.x++ > -1 && s.c[s.x] != 32 && s.c[s.x] != 0 && s.c[s.x] != 44)
			if (e == 0 && (s.c[s.x] < 48 || s.c[s.x] > 57) && ft_pr(s, 7) < 0)
				e++;
	s.x--;
	while (s.x++ > -5 && s.c[s.x] != 32 && s.c[s.x] != 0 && s.c[s.x] != 44)
		if (e == 0 && (s.c[s.x] < 48 || s.c[s.x] > 57) && ft_pr(s, 4) < 0)
			e++;
	if (s.c[s.x] == 44 && s.c[s.x + 1] == 48 && s.c[s.x + 2] == 120
			&& ft_check_hex(s.c, s.x + 2, &e, s) > 0)
		while (s.x++ > -1 && s.c[s.x] != 32 && s.c[s.x] != 0)
			;
	else if (s.c[s.x] == 44)
	{
		if (e++ == 0)
			ft_pr(s, 4);
		while (s.x++ > -1 && s.c[s.x] != 32 && s.c[s.x] != 0)
			;
	}
	if (e != 0)
		s.invalid = e;
	return (s);
}

static t_data	ft_lcheck(t_data s, int num)
{
	s.l++;
	s.x = 0;
	while (s.c[s.x] != 0)
	{
		while (s.c[s.x] == 32)
			s.x++;
		if (s.c[s.x] != 32 && s.c[s.x] != 0 && num++ > -1)
			s = ft_check_number(s, 0);
	}
	if (s.len == -1)
		s.len = num;
	else if (s.len != -1 && num != s.len)
		s.len = -2;
	return (s);
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

static int		**ft_convert(t_data s, int i, int x, int y)
{
	if (!(s.tab = (int **)malloc(sizeof(int *) * s.l)) && ft_pr(s, 9) == -1)
		return (NULL);
	while (s.s[i] != 0 && y < s.l && (x = 0) == 0)
	{
		if (!(s.tab[y] = (int *)malloc(sizeof(int) * s.len)) && ft_pr(s, 9) < 0)
			return (NULL);
		while (x < s.len)
		{
			s.tab[y][x++] = ft_atoi(s.s, &i, 0, 1);
			while (s.s[i] == 32)
				i++;
		}
		y++;
	}
	return (s.tab);
}
int				ft_key_hook(int keycode, t_var *v)
{
	if (keycode == 53)
	{
		mlx_destroy_window(v->mlx, v->win);
		exit(0);
	}
	return (0);
}
static int		ft_draw(t_data s)
{
	t_var v;

	v.i = 0;
	v.mlx = mlx_init();
	while (v.i < 3)
	{
		s.file = s.files[v.i];
		v.win = mlx_new_window(v.mlx, 1600, 900, ft_strjoin("fdf : ", s.file));
		mlx_key_hook(v.win, &ft_key_hook, &v);
		v.i++;
	}
	mlx_loop(v.mlx);
	return (0);
}

static int		ft_execute(t_data s, int fd)
{
	s.l = 0;
	s.len = -1;
	s.invalid = 0;
	s.c = ft_strnew(1);
	s.s = ft_strnew(1);
	if ((fd = open(s.file, O_RDONLY)) == -1)
		return (ft_pr(s, 3));
	while (get_next_line(fd, &s.c, s) > 0 && (s = ft_lcheck(s, 0)).l > -1)
		s.s = ft_strjoin(ft_strjoin(s.s, " "), s.c);
	if (s.len == -2)
		ft_pr(s, 8);
	else if (s.len == 0)
		ft_pr(s, 5);
	else if (s.invalid == 0 && (s.tab = ft_convert(s, 0, 0, 0)) != NULL)
		ft_draw(s);
	if (close(fd) == -1)
		return (ft_pr(s, 3));
	return (0);
}

int				main(int ac, char **av)
{
	t_data	s;

	s.files = av;
	if (ac < 2)
		return (ft_pr(s, 1));
	else if (BUFF_SIZE < 1)
		return (ft_pr(s, 2));
	else
		while (ac > 1 && (s.file = s.files[ac - 1]) != NULL && ac-- > -1)
			ft_execute(s, 0);
	return (0);
}
