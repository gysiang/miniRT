/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/17 10:45:52 by bhowe            ###   ########.fr       */
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
		split_line = ft_split(line, ' ');
		if (split_line || !split_line[0])
		{
			free(line);
			break;
		}
		// use strcmp to check if the first element
		if (!ft_strcmp(split_line[0], "A"))
		{
			if (split_line[1] && split_line[2] && !split_line[3])
			{
				data->amb_light = (int)ft_atoi(split_line[1]);
				// amb rgb values
				rgb_values = ft_split(split_line[2], ',');
				if (rgb_values && rgb_values[0] && rgb_values[1] && rgb_values[2])
				{
					data->amb_rgb[0] = ft_atoi(rgb_values[0]);
					data->amb_rgb[1] = ft_atoi(rgb_values[1]);
					data->amb_rgb[2] = ft_atoi(rgb_values[2]);
				}
				else
					printf("Error: RGB values were not properly allocated.\n");
				free_array(rgb_values);
			}
			else
				printf("Error.\n Incorrect number of elements provided for ambient light\n");
		}
		else if (!ft_strcmp(split_line[0], "C"))
		{
			if (split_line[1] && split_line[2] && split_line[3] && !split_line[4])
			{
				// cam_xyz
				xyz_values = ft_split(split_line[1], ',');
				if (xyz_values && xyz_values[0] && xyz_values[1] && xyz_values[2])
				{
					data->cam_xyz[0] = ft_atoi(xyz_values[0]);
					data->cam_xyz[1] = ft_atoi(xyz_values[1]);
					data->cam_xyz[2] = ft_atoi(xyz_values[2]);
				}
				// cam vector
				cam_vector = ft_split(split_line[2], ',');
				if (cam_vector && cam_vector[0] && cam_vector[1] && cam_vector[2])
				{
					data->cam_vector[0] = ft_atoi(cam_vector[0]);
					data->cam_vector[1] = ft_atoi(cam_vector[1]);
					data->cam_vector[2] = ft_atoi(cam_vector[2]);
				}
				// cam_fov
				data->cam_fov = ft_atoi(split_line[3]);
			}
			else
				printf("Error.\n Incorrect number of elements provided for camera\n");
		}
		else if (ft_strcmp(split_line[0], "L"))
		{
			if (split_line[1] && split_line[2] && split_line[3] && !split_line[4])
			{
				xyz_values = ft_split(split_line[1], ',');
				if (xyz_values && xyz_values[0] && xyz_values[1] && xyz_values[2])
				{
					data->light_xyz[0] = (float)ft_atoi(xyz_values[0]);
					data->light_xyz[1] = (float)ft_atoi(xyz_values[1]);
					data->light_xyz[2] = (float)ft_atoi(xyz_values[2]);
				}
				light_brightness = (float)ft_atoi(split_line[2]);
			}
			else
				printf("Error.\n Incorrect number of elements provided for light.\n");
		}
		else if (ft_strcmp(split_line[0], "sp"))
		{
			if (split_line[1] && split_line[2] && split_line[3] && !split_line[4])
			{
				xyz_values = ft_split(split_line[1], ',');
				if (xyz_values && xyz_values[0] && xyz_values[1] && xyz_values[2])
				{
					data->sphere_xyz[0] = (float)ft_atoi(xyz_values[0]);
					data->sphere_xyz[1] = (float)ft_atoi(xyz_values[1]);
					data->sphere_xyz[2] = (float)ft_atoi(xyz_values[2]);
				}
				data->sphere_dia = (float)ft_atoi(split_line[2]);
				rgb_values = ft_split(split_line[2], ',');
				if (rgb_values && rgb_values[0] && rgb_values[1] && rgb_values[2])
				{
					data->sphere_rgb[0] = ft_atoi(rgb_values[0]);
					data->sphere_rgb[1] = ft_atoi(rgb_values[1]);
					data->sphere_rgb[2] = ft_atoi(rgb_values[2]);
				}
			}
			else
				printf("Error.\n Incorrect number of elements provided for sphere.\n");
		}
		else if (ft_strcmp(split_line[0], "pl"))
		{
			if (split_line[1] && split_line[2] && split_line[3] && !split_line[4])
			{
				xyz_values = ft_split(split_line[1], ',');
				if (xyz_values && xyz_values[0] && xyz_values[1] && xyz_values[2])
				{
					data->plane_xyz[0] = (float)ft_atoi(xyz_values[0]);
					data->plane_xyz[1] = (float)ft_atoi(xyz_values[1]);
					data->plane_xyz[2] = (float)ft_atoi(xyz_values[2]);
				}
				vector_values = ft_split(split_line[2], ',');
				if (vector_values && vector_values[0] && vector_values[1] && vector_values[2])
				{
					data->cam_vector[0] = ft_atoi(vector_values[0]);
					data->cam_vector[1] = ft_atoi(vector_values[1]);
					data->cam_vector[2] = ft_atoi(vector_values[2]);
				}
				rgb_values = ft_split(split_line[3], ',');
				if (rgb_values && rgb_values[0] && rgb_values[1] && rgb_values[2])
				{
					data->plane_rgb[0] = ft_atoi(rgb_values[0]);
					data->plane_rgb[1] = ft_atoi(rgb_values[1]);
					data->plane_rgb[2] = ft_atoi(rgb_values[2]);
				}
			}
			else
				printf("Error.\n Incorrect number of elements provided for sphere.\n");
		}
		else if (ft_strcmp(split_line[0], "cy"))
		{
			if (split_line[1] && split_line[2] && split_line[3] && split_line[4] && !split_line[5])
			{
				xyz_values = ft_split(split_line[1], ',');
				if (xyz_values && xyz_values[0] && xyz_values[1] && xyz_values[2])
				{
					data->cylinder_xyz[0] = (float)ft_atoi(xyz_values[0]);
					data->cylinder_xyz[1] = (float)ft_atoi(xyz_values[1]);
					data->cylinder_xyz[2] = (float)ft_atoi(xyz_values[2]);
				}
				cylinder_vector = ft_split(split_line[2], ',');
				if (cylinder_vector && cylinder_vector[0] && cylinder_vector[1] && cylinder_vector[2])
				{
					data->cylinder_xyz[0] = (float)ft_atoi(cylinder_vector[0]);
					data->cylinder_xyz[1] = (float)ft_atoi(cylinder_vector[1]);
					data->cylinder_xyz[2] = (float)ft_atoi(cylinder_vector[2]);
				}
				data->cylinder_dia = (float)ft_atoi(split_line[3]);
				data->cylinder_height = (double)ft_atoi(split_line[4]);
				rgb_values = ft_split(split_line[4], ',');
				if (rgb_values && rgb_values[0] && rgb_values[1] && rgb_values[2])
				{
					data->cylinder_rgb[0] = ft_atoi(rgb_values[0]);
					data->cylinder_rgb[1] = ft_atoi(rgb_values[1]);
					data->cylinder_rgb[2] = ft_atoi(rgb_values[2]);
				}
			}
		}
		else
			return (printf("Error.\n"), printf("%s", split_line[0]), printf(" is not recognised. Please check your .rt file.\n"));
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
		// open the .rt file
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (printf("Error.\n The file cannot be opened."));
		// save what is in the file into my data obj
		allocate_elements(data, fd);
		// check if all the elements are present and valid, else return a error message
	}
	else
		return (printf("Error.\n Please input one .rt file as the argument."));
	return (0);
}
