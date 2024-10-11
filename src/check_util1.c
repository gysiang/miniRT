/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:31:12 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/11 11:08:23 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_xyz(char *s)
{
	char	**xyz_values;
	int		i;

	if (comma_check(s))
		return (1);
	xyz_values = ft_split(s, ",");
	if (!xyz_values)
		return (1);
	i = 0;
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

int	check_vector(char *s)
{
	int		i;
	char	**vector_values;
	float	vector;

	if (comma_check(s))
		return (1);
	vector_values = ft_split(s, ",");
	if (!vector_values)
		return (1);
	i = 0;
	while (vector_values[i] != NULL)
	{
		if (!ft_isnumeric(vector_values[i]))
			return (free_array(vector_values), 1);
		vector = ft_atof(vector_values[i]);
		if (vector < -1.0 || vector > 1.0)
			return (free_array(vector_values), 1);
		i++;
	}
	free_array(vector_values);
	if (i != 3)
		return (1);
	return (0);
}

int	check_rgb(char *s)
{
	char	**rgb_values;
	int		rgb;
	int		i;

	if (comma_check(s))
		return (1);
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

int	check_fov(char *s)
{
	int	fov;

	if (!ft_isnumeric(s))
		return (1);
	fov = ft_atoi(s);
	if (fov < 0 || fov > 180)
		return (1);
	return (0);
}

int	check_ratio(char *s)
{
	float	ratio;

	ratio = ft_atof(s);
	if (ratio < 0.0 || ratio > 1.0)
		return (1);
	return (0);
}
