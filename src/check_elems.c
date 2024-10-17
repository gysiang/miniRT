/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:17:51 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/16 11:23:51 by bhowe            ###   ########.fr       */
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
		if (check_fov(s[3]) || !ft_isnumeric(s[3]))
			return (ft_error("Camera FOV must be between 0 and 180"));
		data->cam_count++;
	}
	return (0);
}

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
		height = ft_atof(s[4]);
		if (height < EPSILON || !ft_isnumeric(s[4]))
			return (ft_error("Cylinder height is invalid"));
		if (check_rgb(s[5]))
			return (ft_error("Cylinder RGB values are invalid"));
		data->prim_count++;
	}
	return (0);
}
