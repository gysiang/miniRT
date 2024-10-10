/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prims.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:17:51 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 14:16:25 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_spheres(t_data *data, char **s)
{
	float	diameter;

	if (ft_strncmp(s[0], "sp", 2) == 0)
	{
		if (!check_NumOfInputs(s, 4))
			return (ft_error("Proper sphere Usage: <sp x,y,z diameter r,g,b>"));
		if (check_XYZ(s[1]))
			return (ft_error("sphere XYZ coordinates are invalid"));
		diameter = ft_atof(s[2]);
		if (diameter < 0 || !ft_isnumeric(s[2]))
			return (ft_error("sphere diameter is invalid"));
		if (check_RGB(s[3]))
			return (ft_error("sphere RGB values must be between 0 and 255"));
		data->prim_count++;
	}
	return (0);
}

int	check_planes(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "pl") == 0)
	{
		if (!check_NumOfInputs(s, 4))
			return (ft_error("Proper plane Usage: <pl x,y,z u,v,w r,g,b>"));
		if (check_XYZ(s[1]))
			return (ft_error("plane XYZ coordinates are invalid"));
		if (check_Vector(s[2]))
			return (ft_error("plane vector values must be between -1.0 and 1.0"));
		if (check_RGB(s[3]))
			return (ft_error("plane RGB values must be between 0 and 255"));
		data->prim_count++;
	}
	return (0);
}

int	check_cylinders(t_data *data, char **s)
{
	float	diameter;
	float	height;

	if (ft_strcmp(s[0], "cy") == 0)
	{
		if (!check_NumOfInputs(s, 6))
			return (ft_error("Proper cylinder Usage: <cy x,y,z u,v,w diameter height r,g,b>"));
		if (check_XYZ(s[1]))
			return (ft_error("cylinder XYZ coordinates are invalid"));
		if (check_Vector(s[2]))
			return (ft_error("cylinder vector values must be between -1.0 and 1.0"));
		diameter = ft_atof(s[3]);
		if (diameter < 0 || !ft_isnumeric(s[3]))
			return (ft_error("cylinder diameter is invalid"));
		height = ft_atof(s[3]);
		if (height < 0 || !ft_isnumeric(s[4]))
			return (ft_error("cylinder height is invalid"));
		if (check_RGB(s[5]))
			return (ft_error("cylinder RGB values must be between 0 and 255"));
		data->prim_count++;
	}
	return (0);
}

int	check_cones(t_data *data, char **s)
{
	float	diameter;
	float	height;

	if (ft_strcmp(s[0], "cn") == 0)
	{
		if (!check_NumOfInputs(s, 6))
			return (ft_error("Proper Cone Usage: <cy x,y,z u,v,w diameter height r,g,b>"));
		if (check_XYZ(s[1]))
			return (ft_error("Cone XYZ coordinates are invalid"));
		if (check_Vector(s[2]))
			return (ft_error("Cone vector values must be between -1.0 and 1.0"));
		diameter = ft_atof(s[3]);
		if (diameter < 0 || !ft_isnumeric(s[3]))
			return (ft_error("Cone diameter is invalid"));
		height = ft_atof(s[3]);
		if (height < 0 || !ft_isnumeric(s[4]))
			return (ft_error("Cone height is invalid"));
		if (check_RGB(s[5]))
			return (ft_error("Cone RGB values must be between 0 and 255"));
		data->prim_count++;
	}
	return (0);
}
