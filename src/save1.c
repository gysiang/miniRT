/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:05:57 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 21:41:36 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	save_plane(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "pl") == 0)
	{
		save_vector(&data->prims[data->prim_count].position, s[1]);
		save_vector(&data->prims[data->prim_count].vector, s[2]);
		data->prims[data->prim_count].vector
			= vector_normalize(data->prims[data->prim_count].vector);
		save_rgb(&data->prims[data->prim_count].rgb, s[3]);
		data->prims[data->prim_count].p_type = PL;
		data->prim_count++;
	}
	return (0);
}

int	save_cylinder(t_data *data, char **s)
{
	t_cylinder	cy;

	if (ft_strcmp(s[0], "cy") == 0)
	{
		cy.radius = ft_atof(s[3]) / 2;
		cy.height = ft_atof(s[4]);
		data->prims[data->prim_count].p_data.cy = cy;
		save_vector(&data->prims[data->prim_count].position, s[1]);
		save_vector(&data->prims[data->prim_count].vector, s[2]);
		data->prims[data->prim_count].vector
			= vector_normalize(data->prims[data->prim_count].vector);
		save_rgb(&data->prims[data->prim_count].rgb, s[5]);
		data->prims[data->prim_count].p_type = CY;
		data->prim_count++;
	}
	return (0);
}

int	save_rgb(t_rgb *array, char *s)
{
	char	**rgb_values;

	rgb_values = ft_split(s, ",");
	if (!rgb_values)
		return (1);
	array->r = ft_atoi(rgb_values[0]);
	array->g = ft_atoi(rgb_values[1]);
	array->b = ft_atoi(rgb_values[2]);
	free_array(rgb_values);
	return (0);
}

int	save_vector(t_vec *array, char *s)
{
	char	**vector_values;

	vector_values = ft_split(s, ",");
	if (!vector_values)
		return (1);
	array->x = ft_atof(vector_values[0]);
	array->y = ft_atof(vector_values[1]);
	array->z = ft_atof(vector_values[2]);
	free_array(vector_values);
	return (0);
}
