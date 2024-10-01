/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:17:46 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/01 23:25:24 by bhowe            ###   ########.fr       */
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
		save_RGB(&(data->amb_rgb), s[2]);
	}
	return (0);
}

int	save_Camera(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "C", 1) == 0)
	{
		save_XYZ(&(data->camera.position), s[1]);
		save_Vector(&(data->camera.vector), s[2]);
		data->camera.fov = ft_atoi(s[3]);
		data->camera.aspect_ratio = IMG_WIDTH / (float)IMG_HEIGHT;
		data->camera.scale = tan(data->camera.fov * 0.5 * (PI / 180.0));
		data->camera.up_vector = UP_VECTOR;
		data->camera.right_vector = vector_CrossProduct(&data->camera.vector, &data->camera.up_vector);
		data->camera.half_width = tan(data->camera.fov * 0.5 * (PI / 180.0));
		data->camera.half_height = data->camera.half_width / data->camera.aspect_ratio;
	}
	return (0);
}

int	save_Light(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "L", 1) == 0)
	{
		save_XYZ(&(data->light.position), s[1]);
		data->light.brightness = ft_atof(s[2]);
		save_RGB(&(data->light.rgb), "255,255,255");
	}
	return (0);
}

int	save_Sphere(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "sp", 2) == 0)
	{
		/**
		save_XYZ(&(data->sphere.position), s[1]);
		data->sphere.diameter = ft_atof(s[2]);
		save_RGB(&(data->sphere.rgb), s[3]);
		**/
		// save the sphere info in the array;
		if (data->sphere_count < MAX_OBJ)
		{
			save_XYZ(&(data->spheres[data->sphere_count].position),s[1]);
			data->spheres[data->sphere_count].diameter = ft_atof(s[2]);
			data->spheres[data->sphere_count].radius = ft_atof(s[2]) / 2;
			save_RGB(&(data->spheres[data->sphere_count].rgb), s[3]);
			data->sphere_count++;
		}
	}
	return (0);
}
