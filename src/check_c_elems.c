/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_c_elems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 23:48:12 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/10 16:34:42 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_ambient(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "A") == 0)
	{
		if (!check_NumOfInputs(s, 3))
			return (ft_error("Proper Ambient Usage: <A ratio r,g,b>"));
		if (check_Ratio(s[1]) || !ft_isnumeric(s[1]))
			return (ft_error("Ambient ratio must be between 0.0 and 1.0"));
		if (check_RGB(s[2]))
			return (ft_error("Ambient RGB values are invalid"));
		data->amb_count++;
	}
	return (0);
}

int	check_cam(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "C") == 0)
	{
		if (!check_NumOfInputs(s, 4))
			return (ft_error("Proper Camera Usage: <C x,y,z u,v,w fov>"));
		if (check_XYZ(s[1]))
			return (ft_error("Camera XYZ coordinates are invalid"));
		if (check_Vector(s[2]))
			return (ft_error("Camera vector values are invalid"));
		if (check_FOV(s[3]))
			return (ft_error("Camera FOV must be between 0 and 180"));
		data->cam_count++;
	}
	return (0);
}

int	check_lights(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "L") == 0)
	{
		if (!check_NumOfInputs(s, 3))
			return (ft_error("Proper Light Usage: <L x,y,z ratio>"));
		if (check_XYZ(s[1]))
			return (ft_error("Light XYZ coordinates are invalid"));
		if (check_Ratio(s[2]))
			return (ft_error("Light ratio must be between 0.0 and 1.0"));
		data->light_count++;
	}
	return (0);
}
