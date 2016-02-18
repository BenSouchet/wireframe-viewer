/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/02/18 18:25:32 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static int		ft_check_hex(char *s, int x, int *e, t_data d)
{
	int num;

	num = 0;
	while (x++ > -1 && num++ > -1 && s[x] != 32 && s[x] != 0)
		if ((s[x] < 48 || s[x] > 57) && (s[x] < 65 || s[x] > 70) && (*e)++ == 0)
			ft_pr(d, 6);
	if (num != 7 && *e == 0)
		ft_pr(d, 6);
	return (1);
}

static t_data	ft_check_number(t_data s, int x, int e)
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
	if (e != 0 && x != -100)
		s.invalid = e;
	return (s);
}

static t_data	ft_lcheck(t_data s, int num)
{
	int x;

	s.l++;
	s.x = 0;
	while (s.c[s.x] != 0)
	{
		while (s.c[s.x] == 32)
			s.x++;
		if (s.c[s.x] != 32 && (x = s.x) > -1 && num++ > -1)
			s = ft_check_number(s, x, 0);
	}
	if (s.len == -1)
		s.len = num;
	else if (s.len != -1 && num != s.len)
		s.len = -2;
	return (s);
}

static int		ft_get_n_check(t_data s, int fd)
{
	s.l = 0;
	s.len = -1;
	s.invalid = 0;
	s.c = ft_strnew(1);
	if ((fd = open(s.file, O_RDONLY)) == -1)
		return (ft_pr(s, 3));
	while (get_next_line(fd, &s.c, s) > 0)
		s = ft_lcheck(s, 0);
	if (s.len == -2)
		ft_pr(s, 8);
	else if (s.len == 0)
		ft_pr(s, 6);
	/*if (s.invalid != 0)
		printf("map invalide\n");*/
	if (close(fd) == -1)
		return (ft_pr(s, 3));
	return (0);
}

static int		ft_execute(int ac, t_data s, int i)
{
	while (i < ac && (s.file = s.files[i]) != NULL && i++ > -1)
		if (ft_get_n_check(s, 0) != -1)
			;
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
		ft_execute(ac, s, 1);
	return (0);
}
