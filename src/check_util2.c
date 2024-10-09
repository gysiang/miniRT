/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:51:32 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/07 16:30:14 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_Vector(char *s)
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

int	check_FOV(char *s)
{
	int	fov;

	if (!ft_isnumeric(s))
		return (1);
	fov = ft_atoi(s);
	if (fov < 0|| fov > 180)
		return (1);
	return (0);
}

int	check_Ratio(char *s)
{
	float	ratio;

	ratio = ft_atof(s);
	if (ratio < 0.0 || ratio > 1.0)
		return (1);
	return (0);
}
