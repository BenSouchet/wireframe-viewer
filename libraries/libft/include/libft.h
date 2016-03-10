/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 13:30:40 by bsouchet          #+#    #+#             */
/*   Updated: 2016/03/10 14:27:02 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

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
	void		*mlx;   //mlx
	void		*win;   //window
	int			***tab; //tab
	char		**fls;  //files
	int			**val;  //values width & lines
	int			nbr;    //number
	char		*fln;   //filename
	char		*nam;   //name
	int			max;    //maximum
	int			inv;    //invalid
	int			wth;    //width
	char		*lgr;   //large
	int			lns;    //lines
	int			len;    //lenght
	int			p;      //f position
	int			x;      //x position
	int			y;      //y position
	char		*s;     //string
	char		*c;     //content
}				t_var;

int				ft_abs(int n);

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

int				ft_strcmp(char *s1, char *s2);

int				ft_pr(t_var v, int type);
int				get_next_line(int const fd, char **line, t_var v);

#endif
