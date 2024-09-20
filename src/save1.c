/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:05:57 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/20 11:06:35 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	save_Plane(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "pl", 2) == 0)
	{
		save_XYZ(data->plane.position, s[1]);
		save_Vector(data->plane.vector, s[2]);
		save_RGB(data->plane.rgb, s[3]);
	}
	return (0);
}

int	save_Cylinder(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "cy", 2) == 0)
	{
		save_XYZ(data->plane.position, s[1]);
		save_Vector(data->plane.vector, s[2]);
		data->cylinder.diameter = ft_atof(s[3]);
		data->cylinder.height = ft_atof(s[4]);
		save_RGB(data->plane.rgb, s[5]);
	}
	return (0);
}

int	save_RGB(t_rgb array, char *s)
{
	char	**rgb_values;

	rgb_values = ft_split(s, ',');
	if (!rgb_values)
		return (1);
	array.r = ft_atoi(rgb_values[0]);
	array.g = ft_atoi(rgb_values[1]);
	array.b = ft_atoi(rgb_values[2]);
	free_array(rgb_values);
	return (0);
}

int	save_XYZ(t_coords array, char *s)
{
	char **xyz_values;

	xyz_values = ft_split(s, ',');
	if (!xyz_values)
		return (1);
	array.x = ft_atof(xyz_values[0]);
	array.y = ft_atof(xyz_values[1]);
	array.z = ft_atof(xyz_values[2]);
	free_array(xyz_values);
	return (0);
}

int	save_Vector(t_coords array, char *s)
{
	char **vector_values;

	vector_values = ft_split(s, ',');
	if (!vector_values)
		return (1);
	array.x = ft_atof(vector_values[0]);
	array.y = ft_atof(vector_values[1]);
	array.z = ft_atof(vector_values[2]);
	free_array(vector_values);
	return (0);
}
