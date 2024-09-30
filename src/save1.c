/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:05:57 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/26 13:25:32 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	save_Plane(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "pl", 2) == 0)
	{
		if (data->plane_count < MAX_OBJ)
		{
			save_XYZ(&(data->planes[data->plane_count].position), s[1]);
			save_Vector(&(data->planes[data->plane_count].vector), s[2]);
			save_RGB(&(data->planes[data->plane_count].rgb), s[3]);
			data->plane_count++;
		}
	}
	return (0);
}

int	save_Cylinder(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "cy", 2) == 0)
	{
		if (data->cylinder_count < MAX_OBJ)
		{
			save_XYZ(&(data->cylinders[data->cylinder_count].position), s[1]);
			save_Vector(&(data->cylinders[data->cylinder_count].vector), s[2]);
			data->cylinders[data->cylinder_count].diameter = ft_atof(s[3]);
			data->cylinders[data->cylinder_count].height = ft_atof(s[4]);
			save_RGB(&(data->cylinders[data->cylinder_count].rgb), s[5]);
			data->cylinder_count++;
		}
	}
	return (0);
}

int	save_RGB(t_rgb *array, char *s)
{
	char	**rgb_values;

	rgb_values = ft_split(s, ',');
	if (!rgb_values)
		return (1);
	array->r = ft_atoi(rgb_values[0]);
	array->g = ft_atoi(rgb_values[1]);
	array->b = ft_atoi(rgb_values[2]);
	free_array(rgb_values);
	return (0);
}

int	save_XYZ(t_coords *array, char *s)
{
	char **xyz_values;

	xyz_values = ft_split(s, ',');
	if (!xyz_values)
		return (1);
	array->x = ft_atof(xyz_values[0]);
	array->y = ft_atof(xyz_values[1]);
	array->z = ft_atof(xyz_values[2]);
	free_array(xyz_values);
	return (0);
}

int	save_Vector(t_coords *array, char *s)
{
	char **vector_values;

	vector_values = ft_split(s, ',');
	if (!vector_values)
		return (1);
	array->x = ft_atof(vector_values[0]);
	array->y = ft_atof(vector_values[1]);
	array->z = ft_atof(vector_values[2]);
	free_array(vector_values);
	return (0);
}
