/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:17:46 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/11 10:10:22 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	save_filecontents(t_data *data, int fd)
{
	char	*line;
	char	**split_line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, " \t\n\v\f\r");
		free(line);
		if (!split_line)
			continue ;
		if (save_ambientlight(data, split_line) || save_camera(data, split_line)
			|| save_light(data, split_line) || save_sphere(data, split_line)
			|| save_plane(data, split_line) || save_cylinder(data, split_line))
			return (free_array(split_line), 1);
		free_array(split_line);
	}
	return (0);
}

int	save_ambientlight(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "A") == 0)
	{
		data->amb_light = ft_atof(s[1]);
		save_rgb(&(data->amb_rgb), s[2]);
	}
	return (0);
}

int	save_camera(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "C") == 0)
	{
		save_vector(&(data->camera.position), s[1]);
		save_vector(&(data->camera.vector), s[2]);
		data->camera.vector = vector_normalize(data->camera.vector);
		data->camera.fov = ft_atoi(s[3]);
		data->camera.aspect_ratio = (float)IMG_WIDTH / IMG_HEIGHT;
		data->camera.scale = tan(data->camera.fov * 0.5 * (PI / 180.0));
		data->camera.up_vector = vector_create(0, 1, 0);
	}
	return (0);
}

int	save_light(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "L") == 0)
	{
		save_vector(&(data->light.position), s[1]);
		data->light.brightness = ft_atof(s[2]);
		save_rgb(&(data->light.rgb), "255,255,255");
	}
	return (0);
}

int	save_sphere(t_data *data, char **s)
{
	t_sphere	sp;

	if (ft_strcmp(s[0], "sp") == 0)
	{
		sp.radius = ft_atof(s[2]) / 2;
		data->prims[data->prim_count].p_data.sp = sp;
		save_rgb(&data->prims[data->prim_count].rgb, s[3]);
		save_vector(&data->prims[data->prim_count].position, s[1]);
		data->prims[data->prim_count].p_type = SP;
		data->prim_count++;
	}
	return (0);
}
