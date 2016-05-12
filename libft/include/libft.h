/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 13:30:40 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/12 14:44:39 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

# define MSG00 "error: Window size must be greater than 1024 x 576"
# define MSG01 "usage: ./fdf input_file\n       ./fdf ... input_file"
# define MSG02 "error: BUFF_SIZE must be greater than 0"
# define MSG03 "error: "
# define MSG04 " for the input file "
# define MSG05 ")\t --> Invalid character"
# define MSG06 "\t\t\t --> No data in the input file "
# define MSG07 ")\t --> A sign must be followed only by digit(s)"
# define MSG08 ")\t --> Invalid Hexadecimal color code"
# define MSG09 "\t\t\t --> Lines aren't of the same length"
# define MSG10 "\t\t\t --> Memory allocation failure"

# define BUFF_SIZE 1

typedef struct	s_var
{
	void		*img;
	void		*mlx;
	void		*win;
	char		**fls;
	char		*fln;
	char		*nam;
	char		*lgr;
	char		*c;
	char		*d;
	char		*s;
	int			****tab;
	int			**mov;
	int			**val;
	int			*clr;
	int			*dlr;
	int			*rtx;
	int			*rty;
	int			*rtz;
	int			*zmv;
	int			*zom;
	int			add;
	int			bpp;
	int			end;
	int			lns;
	int			nbr;
	int			wth;
	int			max;
	int			len;
	int			inv;
	int			sl;
	int			p;
	int			y;
	int			x;
}				t_var;

int				ft_abs(int n);

int				ft_atoi(char *str, int *k, int r, int s);

void			*ft_memalloc(size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);

void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char const *s, int fd);

size_t			ft_strlen(const char *s);
char			*ft_itoa(int n);
char			*ft_strnew(size_t size);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin2(char *s1, char *s2, int type);

int				ft_strcmp(char *s1, char *s2);

int				ft_pr(t_var *v, int type);
int				ft_rand(int min, int max);

int				dark_color(int clr, int r, int g, int b);

int				get_next_line(int const fd, char **line, t_var *v);

#endif
