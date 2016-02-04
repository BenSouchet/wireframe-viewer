/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/02/04 18:44:54 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_execute(char *str)
{
	if (str)
		;
	return (0);
}

int			main(int ac, char **av)
{
	int i;

	i = 0;
	if (ac < 2)
		write(1, "usage: ./fdf input_file\n       ./fdf ... input_file\n", 52);
	else
	{
		while (i < ac)
			ft_execute(av[i++]);
	}
	return (0);
}
