/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:17:46 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/20 15:01:37 by gyong-si         ###   ########.fr       */
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
	}
	return (0);
}

int	save_Light(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "L", 1) == 0)
	{
		save_XYZ(&(data->light.position), s[1]);
		data->light.brightness = ft_atof(s[2]);
	}
	return (0);
}

int	save_Sphere(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "sp", 2) == 0)
	{
		save_XYZ(&(data->sphere.position), s[1]);
		data->sphere.diameter = ft_atof(s[2]);
		save_RGB(&(data->sphere.rgb), s[3]);
	}
	return (0);
}
