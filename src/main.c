/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/20 15:08:28 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Prints out all the saved data
void	print_data(t_img *data)
{
	printf("Ambient light\n");
	printf("Amient lightning ratio %.1f\n", data->amb_light);
	printf("Amient rgb: %d,%d,%d\n", data->amb_rgb.r, data->amb_rgb.g, data->amb_rgb.b);
	printf("Camera\n");
	printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->camera.position.x, data->camera.position.y, data->camera.position.z);
	printf("Vector Coordinates: %.1f,%.1f,%.1f\n", data->camera.vector.x, data->camera.vector.y, data->camera.vector.z);
	printf("FOV %d\n", data->camera.fov);
	printf("Light\n");
	printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->light.position.x, data->light.position.y, data->light.position.z);
	printf("Light Brightness %.1f\n", data->light.brightness);
	printf("Sphere\n");
	printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->sphere.position.x, data->sphere.position.y, data->sphere.position.z);
	printf("Diameter %.1f\n", data->sphere.diameter);
	printf("Sphere rgb: %d,%d,%d\n", data->sphere.rgb.r, data->sphere.rgb.g, data->sphere.rgb.b);
	printf("Plane\n");
	printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->plane.position.x, data->plane.position.y, data->plane.position.z);
	printf("Vector Coordinates: %.1f,%.1f,%.1f\n", data->plane.vector.x, data->plane.vector.y, data->plane.vector.z);
	printf("Plane rgb: %d,%d,%d\n", data->plane.rgb.r, data->plane.rgb.g, data->plane.rgb.b);
	printf("Cylinder\n");
	printf("XYZ Coordinates: %.1f,%.1f,%.1f\n", data->cylinder.position.x, data->cylinder.position.y, data->cylinder.position.z);
	printf("Vector Coordinates: %.1f,%.1f,%.1f\n", data->cylinder.vector.x, data->cylinder.vector.y, data->cylinder.vector.z);
	printf("Diameter %.1f\n", data->cylinder.diameter);
	printf("Height %.2f\n", data->cylinder.height);
	printf("Cylinder rgb: %d,%d,%d\n", data->cylinder.rgb.r, data->cylinder.rgb.g, data->cylinder.rgb.b);
	printf("All data is printed successfully\n");
}

int	main(int ac, char **av)
{
	t_prog	*program;
	t_img	*data;
	int		fd;

	if (ac == 2)
	{
		program = malloc(sizeof(*program));
		if (!program)
			return (printf("Error.\n Program data failed to initalise."));
		data = malloc(sizeof(*data));
		if (!data)
			return (printf("Error.\n Image data failed to initalise."));
		if (!check_FileType(av[1]))
			return (printf("Error.\nFile provided is not .rt file.\n"));
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (printf("Error.\nThe file cannot be opened."));
		if (check_FileContents(data, fd))
			return (1);
		init_img_data(data);
		lseek(fd, 0, SEEK_SET);
		save_FileContents(data, fd);
		//if (!save_FileContents(data, fd))
		//	print_data(data);
		init_program(program);
	}
	else
		return (printf("Error.\nPlease input one .rt file as the argument.\n"));
	return (0);
}
