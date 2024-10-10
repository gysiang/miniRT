/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_c_elems.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:17:37 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/10 14:17:58 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
