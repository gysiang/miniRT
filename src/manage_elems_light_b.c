/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_elems_light_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:01:21 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/15 15:13:08 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_capital_elements(t_data *data)
{
	if (data->amb_count != 1 || data->cam_count != 1)
		return (ft_error("There must be at least, one Ambient and Camera."));
	return (0);
}

int	check_lights(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "L") == 0)
	{
		if (!check_numofinputs(s, 4))
			return (ft_error("Proper Light Usage: <L x,y,z ratio r,g,b>"));
		if (check_xyz(s[1]))
			return (ft_error("Light XYZ coordinates are invalid"));
		if (check_ratio(s[2]))
			return (ft_error("Light ratio must be between 0.0 and 1.0"));
		if (check_rgb(s[3]))
			return (ft_error("Light RGB values are invalid"));
		data->light_count++;
	}
	return (0);
}

int	setup_elem_data(t_data *data)
{
	data->prims = malloc(data->prim_count * sizeof(t_prim));
	if (!data->prims)
		return (1);
	data->prim_count = 0;
	if (data->light_count)
	{
		data->light_arr = malloc(data->light_count * sizeof(t_light));
		if (!data->light_arr)
			return (1);
		data->light_count = 0;
	}
	return (0);
}

int	save_light(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "L") == 0)
	{
		save_vector(&(data->light_arr[data->light_count].position), s[1]);
		data->light_arr[data->light_count].brightness = ft_atof(s[2]);
		save_rgb(&(data->light_arr[data->light_count].rgb), s[3]);
		data->light_count++;
	}
	return (0);
}
