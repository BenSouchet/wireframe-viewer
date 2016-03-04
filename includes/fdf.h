/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:39:26 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/04 18:22:46 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <fcntl.h>
# include "../libraries/libft/include/libft.h"

typedef struct	s_var
{
	void		*mlx;
	void		*win;
	char		*nbr;
	char		*nam;
	int			len;
	int			i;
}				t_var;

#endif
