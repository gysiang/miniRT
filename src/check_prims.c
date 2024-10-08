/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:17:51 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/07 23:46:40 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_Spheres(t_data *data, char **s)
{
	float	diameter;

	if (ft_strncmp(s[0], "sp", 2) == 0)
	{
		if (!check_NumOfInputs(s, 4))
			return (ft_error("Proper Sphere Usage: <sp x,y,z diameter r,g,b>"));
		if (check_XYZ(s[1]))
			return (ft_error("Sphere XYZ coordinates are invalid"));
		diameter = ft_atof(s[2]);
		if (diameter < 0 || !ft_isnumeric(s[2]))
			return (ft_error("Sphere diameter is invalid"));
		if (check_RGB(s[3]))
			return (ft_error("Sphere RGB values must be between 0 and 255"));
		data->prim_count++;
	}
	return (0);
}

int	check_Planes(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "pl") == 0)
	{
		if (!check_NumOfInputs(s, 4))
			return (ft_error("Proper Plane Usage: <pl x,y,z u,v,w r,g,b>"));
		if (check_XYZ(s[1]))
			return (ft_error("Plane XYZ coordinates are invalid"));
		if (check_Vector(s[2]))
			return (ft_error("Plane vector values must be between -1.0 and 1.0"));
		if (check_RGB(s[3]))
			return (ft_error("Plane RGB values must be between 0 and 255"));
		data->prim_count++;
	}
	return (0);
}

int	check_Cylinders(t_data *data, char **s)
{
	float	diameter;
	float	height;

	if (ft_strcmp(s[0], "cy") == 0)
	{
		if (!check_NumOfInputs(s, 6))
			return (ft_error("Proper Cylinder Usage: <cy x,y,z u,v,w diameter height r,g,b>"));
		if (check_XYZ(s[1]))
			return (ft_error("Cylinder XYZ coordinates are invalid"));
		if (check_Vector(s[2]))
			return (ft_error("Cylinder vector values must be between -1.0 and 1.0"));
		diameter = ft_atof(s[3]);
		if (diameter < 0 || !ft_isnumeric(s[3]))
			return (ft_error("Cylinder diameter is invalid"));
		height = ft_atof(s[3]);
		if (height < 0 || !ft_isnumeric(s[4]))
			return (ft_error("Cylinder height is invalid"));
		if (check_RGB(s[5]))
			return (ft_error("Cylinder RGB values must be between 0 and 255"));
		data->prim_count++;
	}
	return (0);
}
