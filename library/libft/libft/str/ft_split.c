/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:52:48 by axlee             #+#    #+#             */
/*   Updated: 2024/10/07 09:40:27 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_wcount(char const *s, char *set)
{
	int		n;

	n = 0;
	while (*s && is_set(*s, set))
		s++;
	while (*s)
	{
		while (*s && !is_set(*s, set))
			s++;
		n++;
		while (*s && is_set(*s, set))
			s++;
	}
	return (n);
}

static size_t	ft_wordlen(const char *s, char *set)
{
	size_t	i;

	i = 0;
	while (*s && !is_set(*s, set))
	{
		i++;
		s++;
	}
	return (i);
}

char	**ft_split(char const *s, char *set)
{
	int		n;
	char	**ret;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	n = ft_wcount(s, set);
	ret = malloc((n + 1) * sizeof(char *));
	n = 0;
	if (ret)
	{
		while (s[++i])
		{
			if (s[i] && !is_set(s[i], set))
			{
				ret[n] = ft_substr(s, i, ft_wordlen(&s[i], set));
				i = (i + ft_wordlen(&s[i], set) - 1);
				n++;
			}
		}
		ret[n] = NULL;
	}
	return (ret);
}
