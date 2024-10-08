/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:31:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/08 23:34:11 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_FileType(const char *filename)
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

int ft_error(char *msg)
{
	ft_putstr_fd("Error.\n", STDERR_FILENO);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(".\n", STDERR_FILENO);
	return (1);
}

int	check_NumOfInputs(char **s, int n)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	if (i == n)
		return (1);
	return (0);
}

int	check_RGB(char *s)
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

int	check_XYZ(char *s)
{
	char	**xyz_values;
	int		i;

	i = 0;
	xyz_values = ft_split(s, ",");
	if (!xyz_values)
		return (1);
	while (xyz_values[i] != NULL)
	{
		if (!ft_isnumeric(xyz_values[i]))
			return (free_array(xyz_values), 1);
		i++;
	}
	free_array(xyz_values);
	if (i != 3)
		return (1);
	return (0);
}
