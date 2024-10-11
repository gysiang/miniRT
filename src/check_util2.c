/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:51:32 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/11 11:25:57 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_filetype(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (ft_strcmp(filename + len - 3, ".rt") == 0)
		return (1);
	return (0);
}

int	open_file(int *fd, const char *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
		return (1);
	return (0);
}

int	ft_error(char *msg)
{
	ft_putstr_fd("Error.\n", STDERR_FILENO);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(".\n", STDERR_FILENO);
	return (1);
}

int	check_numofinputs(char **s, int n)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	if (i == n)
		return (1);
	return (0);
}

int	comma_check(char *s)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (s[i])
	{
		if (s[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (1);
	return (0);
}
