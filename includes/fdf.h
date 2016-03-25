/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:39:26 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/25 11:14:54 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "../libft/include/libft.h"
# include "../libmlx/includes/mlx.h"

# define BG_COLOR 0x353535
# define BG2_COLOR 0x2D2D2D
# define UI_COLOR 0x84AC00
# define UI2_COLOR 0x647C15
# define OBJ_COLOR 0x777777
# define WIN_W 1280
# define WIN_H 720

t_var	check(t_var v, int num);

int		init_window(t_var v);

int		expose_hook(t_var *v);
int		key_hook(int keycode, t_var *v);
int		close_hook(int button, t_var *v);

t_var	*user_interface(t_var *v);
void	user_interface_texts(t_var *v);
void	mlx_draw(t_var *v, int x, int y);

int		put_pixel(t_var *v, int color);

#endif
