/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/02/09 18:22:15 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

size_t	ft_strlen(const char *str)
{
	size_t l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

void		ft_bzero(void *s, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	ft_putstr_fd(char const *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, (unsigned char *)(&c), 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd((n % 10 + '0'), fd);
	}
	else
		ft_putchar_fd((n + '0'), fd);
}

char		*ft_strnew(size_t size)
{
	char	*text;

	text = (char *)malloc((size + 1) * sizeof(char));
	if (!text)
		return (NULL);
	ft_bzero(text, size);
	text[size] = '\0';
	return (text);
}

char		*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[j])
		j++;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest);
}

char		*ft_strcpy(char *dest, const char *src)
{
	size_t i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;

	if (!s1)
		return (NULL);
	strjoin = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!strjoin)
		return (NULL);
	ft_strcpy(strjoin, s1);
	ft_strcat(strjoin, s2);
	return (strjoin);
}

static int	ft_print_error(t_data s, int type, int value)
{
	s.line_col++;
	if (type == 1)
		write(2, "usage: ./fdf input_file\n       ./fdf ... input_file", 52);
	else if (type == 2)
		write(2, "error: BUFF_SIZE must be greater than 0", 40);
	else if (type == 3)
	{
		ft_putstr_fd(ft_strjoin("error: ", strerror(errno)), 2);
		ft_putstr_fd(ft_strjoin(" for the input file ", s.file), 2);
	}
	else if (type == 4)
	{
		ft_putstr_fd("error: Invalid character (line ", 2);
		ft_putnbr_fd(s.line_nbr, 2);
		ft_putstr_fd(" col ", 2);
		ft_putnbr_fd(s.line_col, 2);
		ft_putstr_fd(ft_strjoin(") in the input file ", s.file), 2);
	}
	else if (type == 5)
		ft_putstr_fd(ft_strjoin("error: No data in the input file ", s.file), 2);
	else if (type == 6)
	{
		ft_putstr_fd("error: Line ", 2);
		ft_putnbr_fd(s.line_nbr, 2);
		ft_putstr_fd(ft_strjoin(" must begin with a digit or a sign in the input file ", s.file), 2);
	}
	else if (type == 7)
	{
		ft_putstr_fd("error: Line ", 2);
		ft_putnbr_fd(s.line_nbr, 2);
		ft_putstr_fd(ft_strjoin(" space at the end of the line in the input file ", s.file), 2);
	}
	write(2, "\n", 1);
	return (value);
}

static int	ft_read(char **str, int fd, t_data s)
{
	int		ret;
	char	*s2;
	char	buf[BUFF_SIZE + 1];

	if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		return (ft_print_error(s, 3, -1));
	buf[ret] = '\0';
	s2 = *str;
	*str = ft_strjoin(*str, buf);
	if (*s2 != 0)
		free(s2);
	return (ret);
}

static int	ft_get_line(char **str, char **line, char *s2)
{
	int		i;
	char	*join;

	i = 0;
	if (*s2 == '\n')
		i = 1;
	*s2 = 0;
	*line = ft_strjoin("", *str);
	if (i == 0 && ft_strlen(*str) != 0)
	{
		*str = ft_strnew(1);
		return (1);
	}
	else if (i == 0 && !(ft_strlen(*str)))
		return (0);
	join = *str;
	*str = ft_strjoin(s2 + 1, "");
	free(join);
	return (i);
}

int			get_next_line(int const fd, char **line, t_data s)
{
	int			ret;
	char		*s2;
	static char	*str;

	if (str == 0)
		str = "";
	if (!line)
		return (-1);
	ret = BUFF_SIZE;
	while (line)
	{
		s2 = str;
		while (*s2 || ret < BUFF_SIZE)
		{
			if (*s2 == '\n' || *s2 == 0 || *s2 == -1)
				return (ft_get_line(&str, line, s2));
			s2++;
		}
		ret = ft_read(&str, fd, s);
		if (ret == -1)
			return (-1);
	}
	return (0);
}

static t_data	ft_lcheck(t_data s)
{
	int i;
	int sp;

	i = 0;
	sp = 0;
	s.line_nbr++;
	while (s.line_cnt[i] != 0)
	{
		if (i == 0 && !(s.line_cnt[0] > 47 && s.line_cnt[0] < 58)
			&& s.line_cnt[0] != 32 && s.line_cnt[0] != 43
			&& s.line_cnt[0] != 45 && i++ > -1)
			ft_print_error(s, 6, -1);
		else if (!(s.line_cnt[i] > 47 && s.line_cnt[i] < 58) && s.line_cnt[i] != 32)
		{
			ft_print_error(s, 4, -1);
			i++;
		}
		while (s.line_cnt[i] > 47 && s.line_cnt[i] < 58)
			i++;
		if (s.line_cnt[i] == 32 && sp++ > -1)
			while (s.line_cnt[i] == 32)
				i++;
	}
	if (s.line_cnt[0] == 0)
		ft_print_error(s, 6, -1);
	//printf("nombre de int: %i\n", sp + 1);
	return (s);
}

static int	ft_get_n_check(t_data s, int fd)
{
	s.line_nbr = 0;
	s.line_cnt = ft_strnew(1);
	if ((fd = open(s.file, O_RDONLY)) == -1)
		return (ft_print_error(s, 3, -1));
	while (get_next_line(fd, &s.line_cnt, s) > 0)
		s = ft_lcheck(s);
	if (s.line_nbr < 1)
		ft_print_error(s, 5, -1);
	if (close(fd) == -1)
		return (ft_print_error(s, 3, -1));
	return (0);
}

static int	ft_execute(int ac, t_data s, int i)
{
	while (i < ac && (s.file = s.files[i]) != NULL && i++ > -1)
	{
		if (ft_get_n_check(s, 0) != -1)
			;
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_data	s;

	s.files = av;
	if (ac < 2)
		return (ft_print_error(s, 1, -1));
	else if (BUFF_SIZE < 1)
		return (ft_print_error(s, 2, -1));
	else
		ft_execute(ac, s, 1);
	return (0);
}
