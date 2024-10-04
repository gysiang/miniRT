/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:05:57 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/03 14:55:14 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	save_Plane(t_data *data, char **s)
{
	t_plane	pl;

	if (ft_strncmp(s[0], "pl", 2) == 0)
	{
		if (data->plane_count < MAX_OBJ)
		{
			// save_Vector(&(data->planes[data->plane_count].position), s[1]);
			// save_Vector(&(data->planes[data->plane_count].vector), s[2]);
			// save_RGB(&(data->planes[data->plane_count].rgb), s[3]);
			save_Vector(&pl.position, s[1]);
			save_Vector(&pl.vector, s[2]);
			save_RGB(&pl.rgb, s[3]);
			data->planes[data->plane_count] = pl;
			data->plane_count++;
			// * Single array version
			data->prims[data->prim_count].p_data.pl = pl;
			data->prims[data->prim_count].p_type = PL;
			data->prim_count++;
		}
	}
	return (0);
}

int	save_Cylinder(t_data *data, char **s)
{
	t_cylinder cy;

	if (ft_strncmp(s[0], "cy", 2) == 0)
	{
		if (data->cylinder_count < MAX_OBJ)
		{
			// save_Vector(&(data->cylinders[data->cylinder_count].position), s[1]);
			// save_Vector(&(data->cylinders[data->cylinder_count].vector), s[2]);
			// data->cylinders[data->cylinder_count].diameter = ft_atof(s[3]);
			// data->cylinders[data->cylinder_count].height = ft_atof(s[4]);
			// save_RGB(&(data->cylinders[data->cylinder_count].rgb), s[5]);
			save_Vector(&cy.position, s[1]);
			save_Vector(&cy.vector, s[2]);
			cy.diameter = ft_atof(s[3]);
			cy.radius = cy.diameter / 2;
			cy.height = ft_atof(s[4]);
			save_RGB(&cy.rgb, s[5]);
			data->cylinders[data->cylinder_count] = cy;
			data->cylinder_count++;
			// * Single array version
			data->prims[data->prim_count].p_data.cy = cy;
			data->prims[data->prim_count].p_type = CY;
			data->prim_count++;
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

int	save_Vector(t_vec *array, char *s)
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
