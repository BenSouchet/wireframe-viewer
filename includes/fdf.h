/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:39:26 by bsouchet          #+#    #+#             */
/*   Updated: 2016/02/09 18:15:42 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <mlx.h>

# define BUFF_SIZE 10

typedef struct	s_data
{
	char		**files;
	char		*file;
	char		*line_cnt;
	int			line_nbr;
	int			line_col;
}				t_data;

#endif
