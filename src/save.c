/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:17:46 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/09 13:21:24 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int save_FileContents(t_data *data, int fd)
{
	char	*line;
	char	**split_line;

	while ((line = get_next_line(fd)) != NULL)
	{
		split_line = ft_split(line, " \t\n\v\f\r");
		free(line);
		if (!split_line)
			continue ;
		if (save_AmbientLight(data, split_line) || save_Camera(data, split_line)
			|| save_Light(data, split_line) || save_Sphere(data, split_line)
			|| save_Plane(data, split_line) || save_Cylinder(data, split_line))
			return (free_array(split_line), 1);
		free_array(split_line);
	}
	printf("Success: All elements have been saved successfully.\n");
	return (0);
}

int	save_AmbientLight(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "A") == 0)
	{
		data->amb_light = ft_atof(s[1]);
		save_RGB(&(data->amb_rgb), s[2]);
	}
	return (0);
}

int	save_Camera(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "C") == 0)
	{
		save_Vector(&(data->camera.position), s[1]);
		save_Vector(&(data->camera.vector), s[2]);
		data->camera.vector = vector_Normalize(data->camera.vector);
		data->camera.fov = ft_atoi(s[3]);
		data->camera.aspect_ratio = (float)IMG_WIDTH / IMG_HEIGHT;
		data->camera.scale = tan(data->camera.fov * 0.5 * (PI / 180.0));
		data->camera.up_vector = vector_create(0, 1, 0);
	}
	return (0);
}

int	save_Light(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "L") == 0)
	{
		save_Vector(&(data->light.position), s[1]);
		data->light.brightness = ft_atof(s[2]);
		save_RGB(&(data->light.rgb), "255,255,255");
	}
	return (0);
}

int	save_Sphere(t_data *data, char **s)
{
	t_sphere	sp;

	if (ft_strcmp(s[0], "sp") == 0)
	{
		sp.radius = ft_atof(s[2]) / 2;
		data->prims[data->prim_count].p_data.sp = sp;
		save_RGB(&data->prims[data->prim_count].rgb, s[3]);
		save_Vector(&data->prims[data->prim_count].position, s[1]);
		data->prims[data->prim_count].p_type = SP;
		data->prim_count++;
	}
	return (0);
}
