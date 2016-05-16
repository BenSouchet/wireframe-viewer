/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:39:26 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/16 13:59:26 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include "../libft/include/libft.h"
# include "../libmlx/includes/mlx.h"

# define GNL get_next_line
# define PI 3.14159265359
# define BG_COLOR 0x353535
# define BG2_COLOR 0x2D2D2D
# define UI_COLOR 0x84AC00
# define UI2_COLOR 0x647C15
# define OBJ_COLOR 0x777777
# define MIN_V 105
# define WIN_W 1280
# define WIN_H 720

t_var	*check(t_var *v, int num);
t_var	*check_edges(t_var *v);

int		expose_hook(t_var *v);
int		key_hook(int keycode, t_var *v);
int		close_hook(int button, t_var *v);

t_var	*background(t_var *v);

t_var	*user_interface(t_var *v, int type);
void	user_interface_texts(t_var *v);

void	mlx_draw(t_var *v, int x, int y);

int		put_pixel(t_var *v, int color, int type);
void	draw_line(t_var *v, int x, int y, int type);

int		rand_color(int r, int g, int b);
int		face_color(t_var *v);

t_var	*init_tab(t_var *v, int y, int x);
t_var	*reset_tab(t_var *v);

#endif
