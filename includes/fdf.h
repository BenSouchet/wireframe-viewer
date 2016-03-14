/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:39:26 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/14 17:25:11 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

# define BG_COLOR 0x353535
# define BG2_COLOR 0x2D2D2D
# define UI_COLOR 0x84AC00
# define UI2_COLOR 0x646B4D
# define WIN_W 1280
# define WIN_H 720

t_var	check(t_var v, int num);

int		init_window(t_var *v);

int		expose_hook(t_var *v);
int		key_hook(int keycode, t_var *v);
int		close_hook(int button, t_var *v);

void	mlx_draw(t_var *v, int x, int y);

#endif
