/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:51:32 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 20:53:39 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_xyz(char *s)
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

int	check_vector(char *s)
{
	int		i;
	char	**vector_values;
	float	vector;

	i = 0;
	vector_values = ft_split(s, ",");
	if (!vector_values)
		return (1);
	while (vector_values[i] != NULL)
	{
		if (!ft_isnumeric(vector_values[i]))
		{
			free_array(vector_values);
			return (1);
		}
		vector = ft_atof(vector_values[i]);
		if (vector < -1.0 || vector > 1.0)
		{
			free_array(vector_values);
			return (1);
		}
		i++;
	}
	free_array(vector_values);
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
