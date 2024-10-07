/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/07 22:27:51 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Prints out all the saved data
// void	print_data(t_data *data)
// {

// 	printf("Ambient light\n");
// 	printf("Amient lightning ratio %.1f\n", data->amb_light);
// 	printf("Amient rgb: %d,%d,%d\n", data->amb_rgb.r, data->amb_rgb.g, data->amb_rgb.b);
// 	printf("Camera\n");
// 	printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->camera.position.x, data->camera.position.y, data->camera.position.z);
// 	printf("Vector Coordinates: %.1f,%.1f,%.1f\n", data->camera.vector.x, data->camera.vector.y, data->camera.vector.z);
// 	printf("FOV %d\n", data->camera.fov);
// 	printf("Light\n");
// 	printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->light.position.x, data->light.position.y, data->light.position.z);
// 	printf("Light Brightness %.1f\n", data->light.brightness);
// 	printf("Camera\n");
// 	printf("Vector : %.1f,%.1f,%.1f\n", data->camera.vector.x, data->camera.vector.y, data->camera.vector.z);
// 	printf("Right Vector : %.1f,%.1f,%.1f\n", data->camera.right_vector.x, data->camera.right_vector.y, data->camera.right_vector.z);
// 	printf("Up Vector : %.1f,%.1f,%.1f\n", data->camera.up_vector.x, data->camera.up_vector.y, data->camera.up_vector.z);

	// printf("Sphere\n");
	// printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->spheres[0].position.x, data->spheres[0].position.y, data->spheres[0].position.z);
	// printf("Diameter %.1f\n", data->spheres[0].diameter);
	// printf("Sphere rgb: %d,%d,%d\n", data->spheres[0].rgb.r, data->spheres[0].rgb.g, data->spheres[0].rgb.b);
	// printf("Plane\n");
	// printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->planes[0].position.x, data->planes[0].position.y, data->planes[0].position.z);
	// printf("Vector Coordinates: %.1f,%.1f,%.1f\n", data->planes[0].vector.x, data->planes[0].vector.y, data->planes[0].vector.z);
	// printf("Plane rgb: %d,%d,%d\n", data->planes[0].rgb.r, data->planes[0].rgb.g, data->planes[0].rgb.b);
	// printf("Cylinder\n");
	// printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->cylinders[0].position.x, data->cylinders[0].position.y, data->cylinders[0].position.z);
	// printf("Vector Coordinates: %.1f,%.1f,%.1f\n", data->cylinders[0].vector.x, data->cylinders[0].vector.y, data->cylinders[0].vector.z);
	// printf("Diameter %.1f\n", data->cylinders[0].diameter);
	// printf("Height %.2f\n", data->cylinders[0].height);
	// printf("Cylinder rgb: %d,%d,%d\n", data->cylinders[0].rgb.r, data->cylinders[0].rgb.g, data->cylinders[0].rgb.b);
	// printf("All data is printed successfully\n");
// }

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac == 2)
	{
		if (!check_FileType(av[1]))
			return (ft_error("File provided is not .rt file"));
		if (open_file(&fd, av[1]))
			return (ft_error(".rt file cannot be opened"));
		data = init_data();
		if (check_FileContents(&data, fd))
			return (1);
		close(fd);
		if (open_file(&fd, av[1]))
			return (ft_error(".rt file cannot be opened"));
		save_FileContents(&data, fd);
		init_program(&data);
	}
	else
		return (ft_error("Please input one .rt file as the argument"));
	return (0);
}
