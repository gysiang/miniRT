/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prims.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:17:51 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 23:07:05 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_spheres(t_data *data, char **s)
{
	float	diameter;

	if (ft_strncmp(s[0], "sp", 2) == 0)
	{
		if (!check_numofinputs(s, 4))
			return (ft_error("Proper Sphere Usage: <sp x,y,z diameter r,g,b>"));
		if (check_xyz(s[1]))
			return (ft_error("Sphere XYZ coordinates are invalid"));
		diameter = ft_atof(s[2]);
		if (diameter < EPSILON || !ft_isnumeric(s[2]))
			return (ft_error("Sphere diameter is invalid"));
		if (check_rgb(s[3]))
			return (ft_error("Sphere RGB values are invalid"));
		data->prim_count++;
	}
	return (0);
}

int	check_planes(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "pl") == 0)
	{
		if (!check_numofinputs(s, 4))
			return (ft_error("Proper Plane Usage: <pl x,y,z u,v,w r,g,b>"));
		if (check_xyz(s[1]))
			return (ft_error("Plane XYZ coordinates are invalid"));
		if (check_vector(s[2]))
			return (ft_error("Plane vector values are invalid"));
		if (check_rgb(s[3]))
			return (ft_error("Plane RGB values are invalid"));
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
		if (!check_numofinputs(s, 6))
			return (ft_error("Proper Cylinder Usage: <cy x,y,z"
					"u,v,w diameter height r,g,b>"));
		if (check_xyz(s[1]))
			return (ft_error("Cylinder XYZ coordinates are invalid"));
		if (check_vector(s[2]))
			return (ft_error("Cylinder vector values are invalid"));
		diameter = ft_atof(s[3]);
		if (diameter < EPSILON || !ft_isnumeric(s[3]))
			return (ft_error("Cylinder diameter is invalid"));
		height = ft_atof(s[3]);
		if (height < EPSILON || !ft_isnumeric(s[4]))
			return (ft_error("Cylinder height is invalid"));
		if (check_rgb(s[5]))
			return (ft_error("Cylinder RGB values are invalid"));
		data->prim_count++;
	}
	return (0);
}
