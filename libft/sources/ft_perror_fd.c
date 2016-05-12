/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 18:01:27 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/12 15:14:59 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_pr2(t_var *v, int type)
{
	if (type == 5)
		ft_putstr_fd(ft_strjoin(ft_strjoin(MSG03, v->fls[v->max]), MSG06), 2);
	else if (type == 6 && v->x++ > -1)
	{
		ft_putstr_fd(ft_strjoin(
		ft_strjoin(MSG03, v->fls[v->max]), " (line "), 2);
		ft_putnbr_fd(v->lns, 2);
		ft_putstr_fd(" col ", 2);
		ft_putnbr_fd(v->x, 2);
		ft_putstr_fd(MSG08, 2);
	}
	else if (type == 7 && v->x++ > -1)
	{
		ft_putstr_fd(ft_strjoin(
		ft_strjoin(MSG03, v->fls[v->max]), " (line "), 2);
		ft_putnbr_fd(v->lns, 2);
		ft_putstr_fd(" col ", 2);
		ft_putnbr_fd(v->x, 2);
		ft_putstr_fd(MSG07, 2);
	}
	else if (type == 8)
		ft_putstr_fd(ft_strjoin(ft_strjoin(MSG03, v->fls[v->max]), MSG09), 2);
	else if (type == 9)
		ft_putstr_fd(ft_strjoin(ft_strjoin(MSG03, v->fls[v->max]), MSG10), 2);
}

int			ft_pr(t_var *v, int type)
{
	if (type == 0)
		write(2, MSG00, 51);
	else if (type == 1)
		write(2, MSG01, 52);
	else if (type == 2)
		write(2, MSG02, 40);
	else if (type == 3)
	{
		ft_putstr_fd(ft_strjoin(MSG03, v->fls[v->max]), 2);
		ft_putstr_fd(ft_strjoin("\t\t\t --> ", strerror(errno)), 2);
	}
	else if (type == 4 && v->x++ > -1)
	{
		ft_putstr_fd(ft_strjoin(
		ft_strjoin(MSG03, v->fls[v->max]), " (line "), 2);
		ft_putnbr_fd(v->lns, 2);
		ft_putstr_fd(" col ", 2);
		ft_putnbr_fd(v->x, 2);
		ft_putstr_fd(MSG05, 2);
	}
	else if (type > 4)
		ft_pr2(v, type);
	write(2, "\n", 1);
	return (-1);
}
