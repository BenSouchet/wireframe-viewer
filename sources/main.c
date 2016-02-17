/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/02/17 19:01:43 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_data	ft_check_number(t_data s)
{
	int w;

	w = 0;
	if (s.c[s.x] == 43 || s.c[s.x] == 45)
		while (s.x++ > -1 && s.c[s.x] != 32 && s.c[s.x] != 0 && s.c[s.x] != 44)
			if (w == 0 && (s.c[s.x] < 48 || s.c[s.x] > 57) && ft_pr(s, 7) == -1)
				w++;
	s.x--;
	while (s.x++ > -5 && s.c[s.x] != 32 && s.c[s.x] != 0 && s.c[s.x] != 44)
		if (w == 0 && (s.c[s.x] < 48 || s.c[s.x] > 57) && ft_pr(s, 4) == -1)
			w++;
	if (s.c[s.x] == 44 && s.c[s.x + 1] == 48 && s.c[s.x + 2] == 120)
		while (s.x++ > -1 && s.c[s.x] != 32 && s.c[s.x] != 0)
			;
	else if (s.c[s.x] == 44)
	{
		ft_pr(s, 6);
		while (s.x++ > -1 && s.c[s.x] != 32 && s.c[s.x] != 0)
			;
	}
	return (s);
}

static t_data	ft_lcheck(t_data s)
{
	int num;

	num = 0;
	s.l++;
	s.x = 0;
	while (s.c[s.x] != 0)
	{
		if (s.c[s.x] == 32)
			while (s.c[s.x] == 32)
				s.x++;
		if (s.c[s.x] != 32 && num++ > -1)
			s = ft_check_number(s);
	}
	return (s);
}

static int		ft_get_n_check(t_data s, int fd)
{
	s.l = 0;
	s.c = ft_strnew(1);
	if ((fd = open(s.file, O_RDONLY)) == -1)
		return (ft_pr(s, 3));
	while (get_next_line(fd, &s.c, s) > 0)
		s = ft_lcheck(s);
	if (s.l < 2)
		ft_pr(s, 5);
	if (close(fd) == -1)
		return (ft_pr(s, 3));
	return (0);
}

static int		ft_execute(int ac, t_data s, int i)
{
	while (i < ac && (s.file = s.files[i]) != NULL && i++ > -1)
	{
		if (ft_get_n_check(s, 0) != -1)
			;
	}
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
