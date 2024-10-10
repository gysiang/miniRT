/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:31:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 20:49:45 by gyong-si         ###   ########.fr       */
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

int	check_rgb(char *s)
{
	char	**rgb_values;
	int		rgb;
	int		i;

	rgb_values = ft_split(s, ",");
	if (!rgb_values)
		return (1);
	i = 0;
	while (rgb_values[i] != NULL)
	{
		if (!ft_isnumeric(rgb_values[i]))
			return (free_array(rgb_values), 1);
		rgb = ft_atoi(rgb_values[i]);
		if (rgb < 0 || rgb > 255)
			return (free_array(rgb_values), 1);
		i++;
	}
	free_array(rgb_values);
	if (i != 3)
		return (1);
	return (0);
}
