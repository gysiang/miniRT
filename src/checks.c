/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:07:02 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/17 21:22:53 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	checkfiletype(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (ft_strcmp(filename + len - 3, ".rt") == 0)
		return (1);
	return (0);
}

char *normalize_whitespace(const char *str)
{
	char *cleaned_str;
	int i = 0;
	int	j = 0;
	int	space_found = 0;

	cleaned_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!cleaned_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\t')
			cleaned_str[j++] = ' ';
		else if (ft_isspace(str[i]))
		{
			if (!space_found)
			{
				cleaned_str[j++] = ' ';
				space_found = 1;
			}
		}
		else
		{
			cleaned_str[j++] = str[i];
			space_found = 0;
		}
		i++;
	}
	cleaned_str[j] = '\0';
	return (cleaned_str);
}

// check ambient values and allocate to data struct
int	check_Ambient(t_img *data, char *line)
{
	char	*norm_line;
	float	amb_light;
	char	**rgb_values;
	char	**str;

	norm_line = normalize_whitespace(line);
	str = ft_split(norm_line, ' ');
	//printf("str[0]: %s\n", str[0]);
	//printf("str[1]: %s\n", str[1]);
	//printf("str[2]: %s\n", str[2]);
	if (ft_strncmp(str[0], "A", 1) == 0)
	{
		if (str[1] && str[2] && !str[3])
		{
			amb_light = (float)ft_atoi(str[1]);
			if (amb_light >= 0.0 && amb_light <= 1.0)
				data->amb_light = amb_light;
			else
			{
				ft_putstr_fd("Error.\nAmbient Light value is not in range.\n", 2);
				return (1);
			}
			rgb_values = ft_split(str[2], ',');
			if (!rgb_values)
			{
				free_array(rgb_values);
				ft_putstr_fd("Error.\nCannot Split Ambient rgb values.\n", 2);
				return (1);
			}
			// need another check to make sure that ther are 3 rgb values
			// also need to make sure number is between 0 to 255
			if (rgb_values[0] && rgb_values[1] && rgb_values[2] && !rgb_values[3])
			{
				data->amb_rgb.r = (int)ft_atoi(rgb_values[0]);
				data->amb_rgb.g = (int)ft_atoi(rgb_values[1]);
				data->amb_rgb.b = (int)ft_atoi(rgb_values[2]);
			}
			else
			{
				free_array(rgb_values);
				ft_putstr_fd("Error.\n There are incorrect number of rgb values.\n", 2);
				return (1);
			}
			free_array(rgb_values);
			printf("Successfully saved ambient elements.\n");;
			return (0);
		}
		else
		{
			ft_putstr_fd("Error\nIncorrect number of arguments for ambient light.\n", 2);
			return (1);
		}
	}
	return (0);
}

int	check_Cam(t_img *data, char *line)
{
	char	**xyz_values;
	char	**vector_values;
	char	**str;
	char	*norm_line;
	int		fov_value;

	norm_line = normalize_whitespace(line);
	str = ft_split(norm_line, ' ');
	if (ft_strncmp(str[0], "C", 1) == 0)
	{
		if (str[1] && str[2] && str[3] && !str[4])
		{
			xyz_values = ft_split(str[1], ',');
			if (!xyz_values)
			{
				free_array(xyz_values);
				ft_putstr_fd("Error.\nCannot Split Camera xyz values.\n", 2);
				return (1);
			}
			// check if there are 3 values
			if (xyz_values[0] && xyz_values[1] && xyz_values[2] && !xyz_values[3])
			{
				data->camera.position.x = (float)ft_atoi(xyz_values[0]);
				data->camera.position.y = (int)ft_atoi(xyz_values[1]);
				data->camera.position.z = (int)ft_atoi(xyz_values[2]);
			}
			else
			{
				ft_putstr_fd("Error.\nThere are incorrect number of cam xyz values.\n", 2);
				free_array(xyz_values);
				return (1);
			}
			vector_values = ft_split(str[2], ',');
			if (!vector_values)
			{
				free_array(vector_values);
				ft_putstr_fd("Error.\nCould not split cam vector values.\n", 2);
				return (1);
			}
			if (vector_values[0] && vector_values[1] && vector_values[2] && !vector_values[3])
			{
				data->camera.vector.x = (int)ft_atoi(vector_values[0]);
				data->camera.vector.y  = (int)ft_atoi(vector_values[1]);
				data->camera.vector.z  = (int)ft_atoi(vector_values[2]);
			}
			else
			{
				free_array(vector_values);
				ft_putstr_fd("Error.\nThere are incorrect number of cam vector values.\n", 2);
				return (1);
			}
			// need to make sure number if from 0 to 180
			// also need to check if it is a number
			fov_value = ft_atoi(str[2]);
			if (fov_value >= 0 && fov_value <= 180)
				data->camera.fov = ft_atoi(str[2]);
			else
			{
				ft_putstr_fd("Error.\nThe Camera fov value is out of range.\n", 2);
				return (1);
			}
			free_array(xyz_values);
			free_array(vector_values);
			printf("Successfully saved Camera elements.\n");
			return (0);
		}
	}
	return (0);
}

int	check_Light(t_img *data, char *line)
{
	char	**xyz_values;
	char	**str;
	char	*norm_line;
	int		light_ratio;

	norm_line = normalize_whitespace(line);
	str = ft_split(norm_line, ' ');
	if (ft_strncmp(str[0], "L", 1) == 0)
	{
		if (str[1] && str[2] && !str[3])
		{
			xyz_values = ft_split(str[1], ',');
			if (!xyz_values)
			{
				free_array(xyz_values);
				return (1);
			}
			// check if there are 3 values
			if (xyz_values[0] && xyz_values[1] && xyz_values[2] && !xyz_values[3])
			{
				data->light.position.x = (float)ft_atoi(xyz_values[0]);
				data->light.position.y = (float)ft_atoi(xyz_values[1]);
				data->light.position.z = (float)ft_atoi(xyz_values[2]);
			}
			else
			{
				ft_putstr_fd("Error.\n There are incorrect number of light xyz values.\n", 2);
				return (1);
			}
			light_ratio = (float)ft_atoi(str[2]);
			if (light_ratio >= 0.0 && light_ratio <= 1.0)
				data->light.brightness = light_ratio;
			else
			{
				ft_putstr_fd("Error.\n The light brightness ration provided is not in range.\n", 2);
				return (1);
			}
			free(xyz_values);
			printf("Successfully saved light elements.\n");
			return (0);
		}
	}
	return (0);
}

int	check_Sp(t_img *data, char *line)
{
	char	**xyz_values;
	char	**rgb_values;
	char	**str;
	char	*norm_line;

	norm_line = normalize_whitespace(line);
	str = ft_split(norm_line, ' ');
	if (ft_strncmp(str[0], "sp", 2) == 0)
	{
		if (str[1] && str[2] && str[3] && !str[4])
		{
			xyz_values = ft_split(str[1], ',');
			if (!xyz_values)
			{
				ft_putstr_fd("Error.\n Could not split sphere xyz values.\n", 2);
				return (1);
			}
			// check if there are 3 values
			if (xyz_values[0] && xyz_values[1] && xyz_values[2] && !xyz_values[3])
			{
				data->sphere.position.x = (float)ft_atoi(xyz_values[0]);
				data->sphere.position.y = (float)ft_atoi(xyz_values[1]);
				data->sphere.position.z = (float)ft_atoi(xyz_values[2]);
			}
			else
			{
				ft_putstr_fd("Error.\n There are incorrect number of sphere xyz values.\n", 2);
				return (1);
			}
			// assign sphere diameter
			data->sphere.diameter = (float)ft_atoi(str[2]);
			// split and assign rgb values
			rgb_values = ft_split(str[3], ',');
			if (!rgb_values)
			{
				ft_putstr_fd("Error.\n Could not split sphere rgb values.\n", 2);
				return (1);
			}
			if (rgb_values[0] && rgb_values[1] && rgb_values[2] && !rgb_values[3])
			{
				data->sphere.rgb.r = (int)ft_atoi(rgb_values[0]);
				data->sphere.rgb.g  = (int)ft_atoi(rgb_values[1]);
				data->sphere.rgb.b = (int)ft_atoi(rgb_values[2]);
			}
			else
			{
				free_array(xyz_values);
				free_array(rgb_values);
				ft_putstr_fd("Error.\n There are incorrect number of sphere rgb values.\n", 2);
				return (1);
			}
			free_array(xyz_values);
			free_array(rgb_values);
			printf("Successfully saved sphere elements.\n");
			return (0);
		}
	}
	return (0);
}

int	check_Cylinder(t_img *data, char *line)
{
	char	**xyz_values;
	char	**vector_values;
	char	**rgb_values;
	char	**str;
	char	*norm_line;

	norm_line = normalize_whitespace(line);
	str = ft_split(norm_line, ' ');
	/**
	printf("str[0]: %s\n", str[0]);
	printf("str[1]: %s\n", str[1]);
	printf("str[2]: %s\n", str[2]);
	printf("str[3]: %s\n", str[3]);
	printf("str[4]: %s\n", str[4]);
	printf("str[5]: %s\n", str[5]);
	*/
	if (ft_strncmp(str[0], "cy", 2) == 0)
	{
		if (str[1] && str[2] && str[3] && str[4] && str[5] && !str[6])
		{
			xyz_values = ft_split(str[1], ',');
			if (!xyz_values)
			{
				ft_putstr_fd("Error.\n Could not split cylinder xyz values.\n", 2);
				return (1);
			}
			// check if there are 3 values
			if (xyz_values[0] && xyz_values[1] && xyz_values[2] && !xyz_values[3])
			{
				data->cylinder.position.x = (float)ft_atoi(xyz_values[0]);
				data->cylinder.position.y = (float)ft_atoi(xyz_values[1]);
				data->cylinder.position.z = (float)ft_atoi(xyz_values[2]);
			}
			else
			{
				ft_putstr_fd("Error.\n There are incorrect number of cylinder xyz values.\n", 2);
				return (1);
			}
			vector_values = ft_split(str[2], ',');
			if (!vector_values)
			{
				ft_putstr_fd("Error.\n Could not split cylinder vector values.\n", 2);
				return (1);
			}
			if (vector_values[0] && vector_values[1] && vector_values[2] && !vector_values[3])
			{
				data->cylinder.vector.x = (float)ft_atoi(vector_values[0]);
				data->cylinder.vector.y = (float)ft_atoi(vector_values[1]);
				data->cylinder.vector.z = (float)ft_atoi(vector_values[2]);
			}
			data->cylinder.diameter = (float)ft_atoi(str[3]);
			data->cylinder.height = (double)ft_atoi(str[4]);
			// assign the rgb values
			rgb_values = ft_split(str[5], ',');
			if (!rgb_values)
			{
				ft_putstr_fd("Error.\n Could not split cylinder rgb values.\n", 2);
				return (1);
			}
			if (rgb_values[0] && rgb_values[1] && rgb_values[2] && !rgb_values[3])
			{
				data->sphere.rgb.r = (int)ft_atoi(rgb_values[0]);
				data->sphere.rgb.g = (int)ft_atoi(rgb_values[1]);
				data->sphere.rgb.b = (int)ft_atoi(rgb_values[2]);
			}
			else
			{
				ft_putstr_fd("Error.\n There are incorrect number of cylinder rgb values.\n", 2);
				return (1);
			}
			free_array(xyz_values);
			free_array(vector_values);
			free_array(rgb_values);
			printf("Successfully saved cylinder elements.\n");
			return (0);
		}
	}
	return (0);
}
