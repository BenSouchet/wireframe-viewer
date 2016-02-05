/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/02/05 14:23:33 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_execute(int ac, char **av)
{
	void *mlx;
	void *win;

	mlx = mlx_init();
	while (i < ac)
		
	return (0);
}

int			main(int ac, char **av)
{
	int i;

	i = 0;
	if (ac < 2)
		write(1, "usage: ./fdf input_file\n       ./fdf ... input_file\n", 52);
	else
		ft_execute(av, ac);
	return (0);
}
