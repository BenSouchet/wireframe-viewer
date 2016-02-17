/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 13:30:40 by bsouchet          #+#    #+#             */
/*   Updated: 2016/02/17 18:53:42 by bsouchet         ###   ########.fr       */
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
# define MSG08 ")\t --> Invalid Hexadecimal color"

# define BUFF_SIZE 1

typedef struct	s_data
{
	char		**files;
	char		*file;
	char		*c;
	int			l;
	int			x;
}				t_data;

int				ft_abs(int n);

void			*ft_memalloc(size_t size);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);

void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char const *s, int fd);

size_t			ft_strlen(const char *s);
char			*ft_strnew(size_t size);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strjoin(char const *s1, char const *s2);

int				ft_pr(t_data s, int type);
int				get_next_line(int const fd, char **line, t_data s);

#endif
