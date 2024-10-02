/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:17:51 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/02 11:43:28 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_Planes(t_img *data, char **s)
{
	if (ft_strncmp(s[0], "pl", 2) == 0)
	{
		if (!check_NumOfInputs(s, 4))
			return (set_error_msg(data, "Error.\nThe number of inputs in Plane is not correct.\n"));
		if (check_XYZ(s[1]))
			return (set_error_msg(data, "Error.\nThe XYZ coordinates in Plane is not valid.\n"));
		if (check_Vector(s[2]))
			return (set_error_msg(data, "Error.\nThe Vector values in Plane is not valid.\n"));
		if (check_RGB(s[3]))
			return (set_error_msg(data, "Error.\nThe RGB values in Plane is not valid.\n"));
	}
	data->prim_count++;
	return (0);
}

int	check_Cylinders(t_img *data, char **s)
{
	float	diameter;
	float	height;

	if (ft_strncmp(s[0], "cy", 2) == 0)
	{
		if (!check_NumOfInputs(s, 6))
			return (set_error_msg(data, "Error.\nThe number of inputs in Cylinder is not correct.\n"));
		if (check_XYZ(s[1]))
			return (set_error_msg(data, "Error.\nThe XYZ coordinates in Cylinder is not valid.\n"));
		if (check_Vector(s[2]))
			return (set_error_msg(data, "Error.\nThe vector values in Cylinder is not valid.\n"));
		diameter = ft_atof(s[3]);
		if (diameter < 0 || !ft_isnumeric(s[3]))
			return (set_error_msg(data, "Error.\nThe diameter of in Cylinder is not valid.\n"));
		height = ft_atof(s[3]);
		if (height < 0 || !ft_isnumeric(s[4]))
			return (set_error_msg(data, "Error.\nThe height of in Cylinder is not valid.\n"));
		if (check_RGB(s[5]))
			return (set_error_msg(data, "Error.\nThe RGB values in Cylinder is not valid.\n"));
	}
	data->prim_count++;
	return (0);
}
