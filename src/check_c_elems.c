/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_c_elems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:48:12 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/10 20:50:53 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_ambients(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "A") == 0)
	{
		if (!check_numofinputs(s, 3))
			return (ft_error("Proper Ambient Usage: <A ratio r,g,b>"));
		if (check_ratio(s[1]) || !ft_isnumeric(s[1]))
			return (ft_error("Ambient ratio must be between 0.0 and 1.0"));
		if (check_rgb(s[2]))
			return (ft_error("Ambient RGB values are invalid"));
		data->amb_count++;
	}
	return (0);
}

int	check_cams(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "C") == 0)
	{
		if (!check_numofinputs(s, 4))
			return (ft_error("Proper Camera Usage: <C x,y,z u,v,w fov>"));
		if (check_xyz(s[1]))
			return (ft_error("Camera XYZ coordinates are invalid"));
		if (check_vector(s[2]))
			return (ft_error("Camera vector values are invalid"));
		if (check_fov(s[3]))
			return (ft_error("Camera FOV must be between 0 and 180"));
		data->cam_count++;
	}
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
		if (check_ratio(s[2]))
			return (ft_error("Light ratio must be between 0.0 and 1.0"));
		data->light_count++;
	}
	return (0);
}
