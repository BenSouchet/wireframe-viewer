/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 18:21:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/02/08 20:17:08 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

size_t		ft_strlen(const char *str)
{
	size_t l;

	l = 0;
	while (str[l])
		l++;
	return (l);
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

void		ft_putstr_fd(char const *s, int fd)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	if (s)
		write(fd, s, i);
}

static int	ft_print_error(char *file, int type, int value)
{
	if (type == 1)
		write(2, "usage: ./fdf input_file\n       ./fdf ... input_file\n", 52);
	else if (type == 2)
		write(2, "error: BUFF_SIZE must be greater than 0\n", 40);
	else if (type == 3)
	{
	ft_putstr_fd(ft_strjoin("error: ", strerror(errno)), 2);
	ft_putstr_fd(ft_strjoin(" for the input ", file), 2);
	ft_putstr_fd("\n", 2);
	}
	return (value);
}

static int	ft_read(char **str, int fd, char *file)
{
	int		ret;
	char	*s;
	char	buf[BUFF_SIZE + 1];

	if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		return (ft_print_error(file, 3, -1));
	buf[ret] = '\0';
	s = *str;
	*str = ft_strjoin(*str, buf);
	if (*s != 0)
		free(s);
	return (ret);
}

static int	ft_get_line(char **str, char **line, char *s)
{
	int		i;
	char	*join;

	i = 0;
	if (*s == '\n')
		i = 1;
	*s = 0;
	*line = ft_strjoin("", *str);
	if (i == 0 && ft_strlen(*str) != 0)
	{
		*str = ft_strnew(1);
		return (1);
	}
	else if (i == 0 && !(ft_strlen(*str)))
		return (0);
	join = *str;
	*str = ft_strjoin(s + 1, "");
	free(join);
	return (i);
}

int			get_next_line(int const fd, char **line, char *file)
{
	int			ret;
	char		*s;
	static char	*str;

	if (str == 0)
		str = "";
	if (!line)
		return (-1);
	ret = BUFF_SIZE;
	while (line)
	{
		s = str;
		while (*s || ret < BUFF_SIZE)
		{
			if (*s == '\n' || *s == 0 || *s == -1)
				return (ft_get_line(&str, line, s));
			s++;
		}
		ret = ft_read(&str, fd, file);
		if (ret == -1)
			return (-1);
	}
	return (0);
}

static int	ft_get_n_check(char *file, int fd)
{
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_print_error(file, 3, 0));
	while (get_next_line(fd, &line, file) > 0)
		;
	//printf("%s\n", line);
	if (close(fd) == -1)
		return (ft_print_error(file, 3, 0));
	return (fd);
}

static int	ft_execute(int ac, char **file, int i)
{
	while (i < ac)
		ft_get_n_check(file[i++], 0);
	return (0);
}

int			main(int ac, char **av)
{
	if (ac < 2)
		ft_print_error(av[0], 1, -1);
	else if (BUFF_SIZE < 1)
		ft_print_error(av[0], 2, -1);
	else
		ft_execute(ac, av, 1);
	return (0);
}
