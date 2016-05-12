/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 17:52:25 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/12 14:41:20 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_read(char **str, int fd, t_var *v)
{
	int		ret;
	char	*s2;
	char	buf[BUFF_SIZE + 1];

	if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		return (ft_pr(v, 3));
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

int			get_next_line(int const fd, char **line, t_var *v)
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
		ret = ft_read(&str, fd, v);
		if (ret == -1)
			return (-1);
	}
	return (0);
}
