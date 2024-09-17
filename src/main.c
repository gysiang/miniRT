/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/17 14:48:14 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_img_data(t_img *data)
{
	// ambient
	data->amb_light = 0;
	data->amb_rgb[0] = 0;
	data->amb_rgb[1] = 0;
	data->amb_rgb[2] = 0;
	// camera
	data->cam_xyz[0] = 0;
	data->cam_xyz[1] = 0;
	data->cam_xyz[2] = 0;
	data->cam_vector[0] = 0;
	data->cam_vector[1] = 0;
	data->cam_vector[2] = 0;
	data->cam_fov = 0;
	// light
	data->light_xyz[0] = 0;
	data->light_xyz[1] = 0;
	data->light_xyz[2] = 0;
	data->light_brightness = 0.00;
	// sphere
	data->sphere_xyz[0] = 0;
	data->sphere_xyz[1] = 0;
	data->sphere_xyz[2] = 0;
	data->sphere_dia = 0;
	data->sphere_rgb[0] = 0;
	data->sphere_rgb[1] = 0;
	data->sphere_rgb[2] = 0;
	// cylinder
	data->cylinder_xyz[0] = 0;
	data->cylinder_xyz[1] = 0;
	data->cylinder_xyz[2] = 0;
	data->cylinder_dia = 0.0;
	data->cylinder_height = 0.00;
	data->cylinder_rgb[0] = 0;
	data->cylinder_rgb[1] = 0;
	data->cylinder_rgb[2] = 0;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// check ambient values and allocate to data struct
int	check_Ambient(t_img *data, char **str)
{
	char**	rgb_values;

	if (ft_strcmp(str, "A") == 0)
	{
		if (str[1] && str[2] && !str[3])
		{
			rgb_values = ft_split(str[1], " ");
			if (!rgb_values)
				return (handle_error("Error.\n Could not split ambient rgb values.\n", rgb_values));
			// need another check to make sure that ther are 3 rgb values
			// also need to make sure number is between 0 to 255
			if (rgb_values[0] && rgb_values[1] && rgb_values[2] && !rgb_values[3])
			{
				data->amb_rgb[0] = (int)ft_atoi(rgb_values[0]);
				data->amb_rgb[1] = (int)ft_atoi(rgb_values[1]);
				data->amb_rgb[2] = (int)ft_atoi(rgb_values[2]);
			}
			else
				handle_error("Error.\n There are incorrect number of rgb values.", rgb_values);
			free_array(rgb_values);
			ft_putstr_fd("Successfully allocated rgb values.\n", 1);
			return (0);
		}
	}
	return (handle_error("Error.\n Ambient light identifier (A) is not found.\n", NULL));
}

int	check_Cam(t_img *data, char **str)
{
	char	**xyz_values;
	char	**vector_values;
	int		fov_value;

	if (ft_strcmp(str, "C") == 0)
	{
		if (str[1] && str[2] && str[3] && !str[4])
		{
			xyz_values = ft_split(str[1], ",");
			if (!xyz_values)
				return (handle_error("Error.\n Could not split cam xyz values.\n", xyz_values));
			// check if there are 3 values
			if (xyz_values[0] && xyz_values[1] && xyz_values[2] && !xyz_values[3])
			{
				data->cam_xyz[0] = (float)ft_atoi(xyz_values[0]);
				data->cam_xyz[1] = (int)ft_atoi(xyz_values[1]);
				data->cam_xyz[2] = (int)ft_atoi(xyz_values[2]);
			}
			else
				return (handle_error("Error.\n There are incorrect number of cam xyz values.\n", xyz_values));
			vector_values = ft_split(str[2], ",");
			if (!vector_values)
				return (handle_error("Error.\n Could not split cam vector values.\n", xyz_values));
			if (vector_values[0] && vector_values[1] && vector_values[2] && !vector_values[3])
			{
				data->cam_vector[0] = (int)ft_atoi(vector_values[0]);
				data->cam_vector[1] = (int)ft_atoi(vector_values[1]);
				data->cam_vector[2] = (int)ft_atoi(vector_values[2]);
			}
			else
				return (handle_error("Error.\n There are incorrect number of cam vector values.\n", xyz_values));
			// need to make sure number if from 0 to 180
			// also need to check if it is a number
			fov_value = ft_atoi(str[2]);
			if (ft_isnumeric(fov_value) && fov_value >= 0 && fov_value <= 180)
				data->cam_fov = ft_atoi(str[2]);
			else
				return (handle_error("Error.\n The cam fov value provided is not in range.\n", NULL));
			free_array(xyz_values);
			free_array(vector_values);
			ft_putstr_fd("Successfully allocated cam values.\n", 1);
			return (0);
		}
	}
	return (handle_error("Error.\n Camera identifier (C) is not found.\n", NULL));
}

int	check_Light(t_img *data, char **str)
{
	char	**xyz_values;
	int		light_ratio;

	if (ft_strcmp(str, "L") == 0)
	{
		if (str[1] && str[2] && !str[3])
		{
			xyz_values = ft_split(str[1], ",");
			if (!xyz_values)
				return (handle_error("Error.\n Could not split cam xyz values.\n", xyz_values));
			// check if there are 3 values
			if (xyz_values[0] && xyz_values[1] && xyz_values[2] && !xyz_values[3])
			{
				data->cam_xyz[0] = (float)ft_atoi(xyz_values[0]);
				data->cam_xyz[1] = (float)ft_atoi(xyz_values[1]);
				data->cam_xyz[2] = (float)ft_atoi(xyz_values[2]);
			}
			else
				return (handle_error("Error.\n There are incorrect number of light xyz values.\n", xyz_values));
			light_ratio = (float)ft_atoi(str[2]);
			if (ft_isnumeric(light_ratio) && light_ratio >= 0.0 && light_ratio <= 1.0)
				data->light_brightness = light_ratio;
			else
				return (handle_error("Error.\n The light brightness ration provided is not in range.\n", NULL));
			free(xyz_values);
			ft_putstr_fd("Successfully allocated light values.\n", 1);
			return (0);
		}
	}
	return (handle_error("Error.\n Light identifier (L) is not found.\n", NULL));
}

int	check_Sp(t_img *data, char **str)
{
	char	**xyz_values;
	char	**rgb_values;

	if (ft_strcmp(str[0], "sp" == 0))
	{
		if (str[1] && str[2] && str[3] && !str[4])
		{
			xyz_values = ft_split(str[1], ",");
			if (!xyz_values)
				return (handle_error("Error.\n Could not split sphere xyz values.\n", xyz_values));
			// check if there are 3 values
			if (xyz_values[0] && xyz_values[1] && xyz_values[2] && !xyz_values[3])
			{
				data->cam_xyz[0] = (float)ft_atoi(xyz_values[0]);
				data->cam_xyz[1] = (float)ft_atoi(xyz_values[1]);
				data->cam_xyz[2] = (float)ft_atoi(xyz_values[2]);
			}
			else
				return (handle_error("Error.\n There are incorrect number of sphere xyz values.\n", xyz_values));
			// assign sphere diameter
			data->sphere_dia = (float)ft_atoi(str[2]);
			// split and assign rgb values
			rgb_values = ft_split(str[3], ",");
			if (!rgb_values)
				return (handle_error("Error.\n Could not split sphere rgb values.\n", xyz_values));
			if (rgb_values[0] && rgb_values[1] && rgb_values[2] && !rgb_values[3])
			{
				data->sphere_rgb[0] = (int)ft_atoi(rgb_values[0]);
				data->sphere_rgb[1] = (int)ft_atoi(rgb_values[1]);
				data->sphere_rgb[2] = (int)ft_atoi(rgb_values[2]);
			}
			else
				return (handle_error("Error.\n There are incorrect number of sphere rgb values.\n", rgb_values));
			free_array(xyz_values);
			free_array(rgb_values);
			ft_putstr_fd("Successfully allocated sphere values.\n", 1);
			return (0);
		}
	}
	return (handle_error("Error.\n Sphere (sp) identifier is not found\n", NULL));
}

int	check_Cylinder(t_img *data, char **str)
{
	char	**xyz_values;
	char	**vector_values;
	char	**rgb_values;

	if (ft_strcmp(str[0], "cy") == 0)
	{
		if (str[1] && str[2] && str[3] && str[4] && !str[5])
		{
			xyz_values = ft_split(str[1], ",");
			if (!xyz_values)
				return (handle_error("Error.\n Could not split sphere xyz values.\n", xyz_values));
			// check if there are 3 values
			if (xyz_values[0] && xyz_values[1] && xyz_values[2] && !xyz_values[3])
			{
				data->cam_xyz[0] = (float)ft_atoi(xyz_values[0]);
				data->cam_xyz[1] = (float)ft_atoi(xyz_values[1]);
				data->cam_xyz[2] = (float)ft_atoi(xyz_values[2]);
			}
			else
				return (handle_error("Error.\n There are incorrect number of cylinder xyz values.\n", xyz_values));
			// assign vector values;
			vector_values = ft_split(str[2], ",");
			if (!vector_values)
				return (handle_error("Error.\n Could not split cam vector values.\n", xyz_values));
			if (vector_values[0] && vector_values[1] && vector_values[2] && !vector_values[3])
			{
				data->cylinder_vector[0] = (float)ft_atoi(vector_values[0]);
				data->cylinder_vector[1] = (float)ft_atoi(vector_values[1]);
				data->cylinder_vector[2] = (float)ft_atoi(vector_values[2]);
			}
			// need to make sure these are numeric too.
			data->cylinder_dia = (float)ft_atoi(str[2]);
			data->cylinder_height = (double)ft_atoi(str[3]);
			// assign the rgb values
			rgb_values = ft_split(str[3], ",");
			if (!rgb_values)
				return (handle_error("Error.\n Could not split sphere rgb values.\n", xyz_values));
			if (rgb_values[0] && rgb_values[1] && rgb_values[2] && !rgb_values[3])
			{
				data->sphere_rgb[0] = (int)ft_atoi(rgb_values[0]);
				data->sphere_rgb[1] = (int)ft_atoi(rgb_values[1]);
				data->sphere_rgb[2] = (int)ft_atoi(rgb_values[2]);
			}
			else
				return (handle_error("Error.\n There are incorrect number of cylinder rgb values.\n", rgb_values));
			free_array(xyz_values);
			free_array(vector_values);
			free_array(rgb_values);
			ft_putstr_fd("Successfully allocated sphere values.\n", 1);
			return (0);
		}
	}
	return (handle_error("Error.\n Cylinder (cy) identifier is not found\n", NULL));
}

int	allocate_elements(t_img *data, int fd)
{
	char	*line;
	char	**split_line;
	char	**rgb_values;
	char	**xyz_values;
	char	**cam_vector;
	char	**cylinder_vector;
	char	**vector_values;
	float	light_brightness;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		// use ft_split on the line, first element will be the element name
		split_line = ft_split(line, " ");
		if (!split_line)
			return (handle_error("Error.\n Could not split the elements in the .rt file.\n", NULL));
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_img *data;
	int		i;
	int		fd;

	if (ac == 2)
	{
		data = malloc(sizeof(*data));
		if (!data)
			return (printf("Error.\n Image failed to initalise."));
		// init the struct
		init_img_data(data);
		// check the extension of the .rt file
		i = checkfiletype(av[1]);
		if (!i)
			return (printf("Error.\n File provided is not .rt file."));
		/**
		// open the .rt file
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (printf("Error.\n The file cannot be opened."));
		// save what is in the file into my data obj
		allocate_elements(data, fd);
		// check if all the elements are present and valid, else return a error message
		**/
	}
	else
		return (printf("Error.\n Please input one .rt file as the argument."));
	return (0);
}
