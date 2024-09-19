/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:17:51 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/19 14:16:50 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * breaks the check functions into checking only.
 */

int	check_NumOfInputs(t_img *data, char **s, int n)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	if (i == n)
		return (1);
	return (0);
}

int	check_RGB(t_img *data, char *s)
{
	char	**rgb_values;
	int		rgb;
	int		i;

	rgb_values = ft_split(s, ',');
	if (!rgb_values)
		return (1);
	i = 0;
	while (rgb_values[i] != NULL)
	{
		if (!ft_isnumeric(rgb_values[i]))
		{
			free_array(rgb_values);
			return (1);
		}
		rgb = ft_atoi(rgb_values[i]);
		if (rgb < 0 || rgb > 255)
		{
			free_array(rgb_values);
			return (1);
		}
		i++;
	}
	free_array(rgb_values);
	return (0);
}

int	check_XYZ(t_img *data, char *s)
{
	char	**xyz_values;
	int		i;

	i = 0;
	xyz_values = ft_split(s, ',');
	if (!xyz_values)
		return (1);
	while (xyz_values[i] != NULL)
	{
		if (!ft_isnumeric(xyz_values[i]))
			return (1);
		i++;
	}
	free_array(xyz_values);
	return (0);
}

int	check_Vector(t_img *data, char *s)
{
	int		i;
	char	**vector_values;
	char	*vector;

	i = 0;
	while (vector_values[i] != NULL)
	{
		if (ft_isnumeric(vector_values[i]))
		{
			free_array(vector_values);
			return (1);
		}
		vector = ft_atoi(vector_values[i]);
		if (-1 < vector || vector > 1)
		{
			free_array(vector_values);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_FOV(t_img *data, char *s)
{
	int	fov;

	if (!ft_isnumeric(s[3]))
		return (1);
	fov = ft_atoi(s[3]);
	if (0 < fov || fov > 180)
		return (1);
	return (0);
}

int	check_Ratio(t_img *data, char *s)
{
	float	ratio;

	ratio = ft_atoi(s[2]);
	if (ratio < 0.0 || ratio > 1.0)
		return (1);
	return (0);
}

int	check_Ambients(t_img *data, char *s)
{
	int		i;

	i = 0;
	if (ft_strncmp(s[0], "A", 1) == 0)
	{
		if (!check_NumOfInputs(data, s, 3))
		{
			data->error_msg = "The number of inputs in ambient is not correct.\n";
			return (1);
		}
		if (check_Ratio(data, s[1]))
			return (1);
		if (check_RGB(data, s[2]))
			return (1);
	}
	return (0);
}

int	check_Cams(t_img *data, char **s)
{
	int		i;

	i = 0;
	if (ft_strncmp(s[0], "C", 1) == 0)
	{
		if (!check_NumOfInputs(data, s, 4))
			return (1);
		if (check_XYZ(data, s[1]))
			return (1);
		if (check_Vector(data, s[2]))
			return (1);
		if (check_FOV(data, s[3]))
			return (1);
	}
	return (0);
}

int	check_Lights(t_img *data, char **s)
{
	int		i;

	i = 0;
	if (ft_strncmp(s[0], "L", 1) == 0)
	{
		if (!check_NumOfInputs(data, s, 3))
			return (1);
		if (check_XYZ(data, s[1]))
			return (1);
		if (check_Ratio(data, s[2]))
			return (1);
	}
	return (0);
}

int	check_Spheres(t_img *data, char **s)
{
	float	diameter;
	int		i;

	i = 0;
	if (ft_strncmp(s[0], "L", 1) == 0)
	{
		if (!check_NumOfInputs(data, s, 4))
			return (1);
		if (check_XYZ(data, s[1]))
			return (1);
		diameter = (float)ft_atoi(s[2]);
		if (diameter < 0)
			return (1);
		if (check_RGB(data, s[3]))
			return (1);
	}
	return (0);
}

int	check_Planes(t_img *data, char **s)
{
	int	i;

	i = 0;
	if (ft_strncmp(s[0], "pl", 2) == 0)
	{
		if (!check_NumOfInputs(data, s, 4))
			return (1);
		if (check_XYZ(data, s[1]))
			return (1);
		if (check_Vector(data, s[2]))
			return (1);
		if (check_RGB(data, s[3]))
			return (1);
	}
	return (0);
}

int	check_Cylinders(t_img *data, char **s)
{
	int		i;
	int		vector;
	int		rgb;
	char	**xyz_values;
	char	**vector_values;
	char	**rgb_values;

	i = 6;
	if (ft_strncmp(s[0], "cy", 2) == 0)
	{
		if (!check_NumOfInputs(data, s, 6))
			return (1);
		if (check_XYZ(data, s[1]))
			return (1);
		if (check_Vector(data, s[2]))
			return (1);
		if (!ft_isnumeric(s[3]))
			return (1);
		if (!ft_isnumeric(s[4]))
			return (1);
		if (check_RGB(data, s[5]))
			return (1);
	}
}
