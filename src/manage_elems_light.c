/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_elems_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:01:21 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/16 11:24:50 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_capital_elements(t_data *data)
{
	if (data->amb_count != 1 || data->cam_count != 1 || data->light_count != 1)
		return (ft_error("There must be one Ambient, Camera and Light"));
	return (0);
}

int	check_lights(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "L") == 0)
	{
		if (!check_numofinputs(s, 3))
			return (ft_error("Proper Light Usage: <L x,y,z ratio>"));
		if (check_xyz(s[1]))
			return (ft_error("Light XYZ coordinates are invalid"));
		if (check_ratio(s[2]) || !ft_isnumeric(s[2]))
			return (ft_error("Light ratio must be between 0.0 and 1.0"));
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
