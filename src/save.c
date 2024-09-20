/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:17:46 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/20 11:02:14 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int save_FileContents(t_img *data, int fd)
{
	char	*line;
	char	*norm_line;
	char	**split_line;
	int		error_flag;

	error_flag = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		norm_line = normalize_whitespace(line);
		split_line = ft_split(norm_line, ' ');
		if (save_AmbientLight(data, split_line) || save_Camera(data, split_line) ||
			save_Light(data, split_line) || save_Sphere(data, split_line) ||
			save_Plane(data, split_line) || save_Cylinder(data, split_line))
		{
			error_flag = 1;
			break;
		}
		free(line);
	}
	if (line != NULL)
	{
		free(line);
		free_array(split_line);
	}
	if (!error_flag)
		printf("Success: All elements have been saved successfully.\n");
	return (error_flag);
}

int	save_AmbientLight(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "A", 1) == 0)
	{
		data->amb_light = ft_atof(s[1]);
		save_RGB(data->amb_rgb, s[2]);
	}
	return (0);
}

int	save_Camera(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "C", 1) == 0)
	{
		save_XYZ(data->camera.position, s[1]);
		save_Vector(data->camera.vector, s[2]);
		data->camera.fov = ft_atoi(s[3]);
	}
	return (0);
}

int	save_Light(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "L", 1) == 0)
	{
		save_XYZ(data->light.position, s[1]);
		data->light.brightness = ft_atof(s[2]);
	}
	return (0);
}

int	save_Sphere(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "sp", 2) == 0)
	{
		save_XYZ(data->sphere.position, s[1]);
		data->sphere.diameter = ft_atof(s[2]);
		save_RGB(data->sphere.rgb, s[3]);
	}
	return (0);
}

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
