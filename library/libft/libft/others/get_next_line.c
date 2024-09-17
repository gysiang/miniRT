/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:07:42 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/16 10:41:43 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

static size_t	find_nlen(char *s)
{
	char	*n;

	n = ft_strchr(s, '\n');
	if (n)
		return ((size_t)(n - s) + 1);
	else
		return (ft_strlen(s));
}

static char	*trim_a_nl(char *s, size_t len)
{
	char	*res;

	if (len > 0)
		len -= 1;
	res = ft_calloc(len + 1, sizeof(char));
	res = ft_memcpy(res, s, len);
	res[len] = '\0';
	free(s);
	if (res[0])
		return (res);
	else
	{
		free(res);
		return (0);
	}
}

static void	save_rem(char *s, char *save, size_t nlen)
{
	size_t	len;

	len = ft_strlen(s) - nlen;
	if (len)
		ft_memcpy(save, s + nlen, len);
	save[len] = '\0';
}

static char	*read_file(int fd, char *str, char buf_read[])
{
	char	*res;
	ssize_t	bytesread;

	bytesread = 1;
	while (bytesread > 0 && !ft_strchr(buf_read, '\n'))
	{
		bytesread = read(fd, buf_read, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(str);
			return (0);
		}
		buf_read[bytesread] = '\0';
		res = ft_strjoin(str, buf_read);
		free(str);
		str = res;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		buf_read[BUFFER_SIZE + 1];
	static char	save[10000];
	size_t		nlen;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (save[0])
		str = ft_strdup(save);
	else
		str = ft_calloc(1, sizeof(char));
	if (!str)
		return (0);
	ft_bzero(buf_read, BUFFER_SIZE + 1);
	str = read_file(fd, str, buf_read);
	nlen = find_nlen(str);
	save_rem(str, save, nlen);
	str = trim_a_nl(str, nlen);
	return (str);
}
