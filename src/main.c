/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/18 12:15:51 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_Ambients(t_img *data, char **s)
{
	char	**rgb_values;
	int		i;
	float 	ratio;
	int		rgb;

	i = 0;
	// check for the first input to see if its a A
	if (ft_strncmp(s[0], "A", 1) == 0)
	{
		// check how many inputs were given, must be equal to 3
		while (s[i] != NULL)
			i++;
		if (i != 3)
			return (1);
		// check if the inputs are numeric
		// split the rgb and check if all given data is numeric
		rgb_values = ft_split(s[2], ',');
		if (!rgb_values)
			return (1);
		// if any of the values are not numeric change
		if (!ft_isnumeric(rgb_values[0]) || !ft_isnumeric(rgb_values[1])
			|| !ft_isnumeric(rgb_values[2]) || !ft_isnumeric(s[1]))
			return (1);
		// lightning ration must be between 0.0 to 1.0
		ratio = (float)ft_atoi(s[1]);
		if (ratio < 0.0 || ratio > 1.0)
			return (1);
		// RGB range should be between 0 - 255
		i = 0;
		while (rgb_values[i] != NULL)
		{
			rgb = ft_atoi(rgb_values[i]);
			if (0 < rgb || rgb > 255)
				return (1);
			i++;
		}
		free_array(rgb_values);
	}
	return (0);
}

int	check_Cams(t_img *data, char **s)
{
	int		i;
	int		vector;
	int		fov;
	char	**xyz_values;
	char	*vector_values;

	i = 0;
	if (ft_strncmp(s[0], "C", 1) == 0)
	{
		// check number of inputs
		while (s[i] != 0)
			i++;
		if (i != 4)
			return (1);
		// check if all the xyz are numeric
		xyz_values = ft_split(s[1], " ");
		i = 0;
		while (xyz_values[i] != NULL)
		{
			if (!ft_isnumeric(xyz_values[i]))
				return (1);
			i++;
		}
		// check if all the vector is in the range of -1 & 1
		i = 0;
		vector_values = ft_split(s[2], " ");
		while (vector_values[i] != NULL)
		{
			// make sure vector values are numeric
			if (!ft_isnumeric(vector_values[i]))
				return (1);
			vector = (float)ft_atoi(vector_values[i]);
			if (-1 < vector || vector > 1)
				return (1);
			i++;
		}
		// check if the FOV is between 0 and 180
		if (!ft_isnumeric(s[3]))
			return (1);
		fov = ft_atoi(s[3]);
		if (0 < fov || fov > 180)
			return (1);
		free_array(xyz_values);
		free_array(vector_values);
	}
	return (0);
}

int	check_Lights(t_img *data, char **s)
{
	char	**xyz_values;
	float	ratio;
	int		i;

	i = 0;
	if (ft_strncmp(s[0], "L", 1) == 0)
	{
		// check number of inputs
		while (s[i] != 0)
			i++;
		if (i != 3)
			return (1);
		xyz_values = ft_split(s[1], " ");
		i = 0;
		while (xyz_values[i] != NULL)
		{
			if (!ft_isnumeric(xyz_values[i]))
				return (1);
			i++;
		}
		ratio = (float)ft_atoi(s[2]);
		if (ratio < 0.0 || ratio > 1.0)
			return (1);
		free_array(xyz_values);
	}
	return (0);
}

int	check_Spheres(t_img *data, char **s)
{
	float	diameter;
	int		i;
	int		rgb;
	char	**xyz_values;
	char	**rgb_values;

	i = 0;
	if (ft_strncmp(s[0], "L", 1) == 0)
	{
		// check number of inputs
		while (s[i] != 0)
			i++;
		if (i != 4)
			return (1);
		xyz_values = ft_split(s[1], " ");
		i = 0;
		while (xyz_values[i] != NULL)
		{
			if (!ft_isnumeric(xyz_values[i]))
				return (1);
			i++;
		}
		diameter = (float)ft_atoi(s[2]);
		if (diameter < 0)
			return (1);
		i = 0;
		rgb_values = ft_split(s[3], " ");
		while (rgb_values[i] != NULL)
		{
			if (!ft_isnumeric(rgb_values[i]))
				return (1);
			rgb = ft_atoi(rgb_values[i]);
			if (0 < rgb || rgb > 255)
				return (1);
			i++;
		}
		free_array(xyz_values);
		free_array(rgb_values);
	}
	return (0);
}

int	check_Planes(t_img *data, char **s)
{
	int	i;
	int	vector;
	int	rgb;
	char	**xyz_values;
	char	**vector_values;
	char	**rgb_values;

	i = 0;
	if (ft_strncmp(s[0], "pl", 2) == 0)
	{
		while (s[i] != 0)
			i++;
		if (i != 4)
			return (1);
		xyz_values = ft_split(s[1], " ");
		i = 0;
		while (xyz_values[i] != NULL)
		{
			if (!ft_isnumeric(xyz_values[i]))
				return (1);
			i++;
		}
		free_array(xyz_values);
		i = 0;
		vector_values = ft_split(s[2], " ");
		while (vector_values[i] != NULL)
		{
			if (!ft_isnumeric(vector_values[i]))
				return (1);
			vector = (float)ft_atoi(vector_values[i]);
			if (-1 < vector || vector > 1)
				return (1);
			i++;
		}
		free_array(vector_values);
		i = 0;
		rgb_values = ft_split(s[3], " ");
		while (rgb_values[i] != NULL)
		{
			if (!ft_isnumeric(rgb_values[i]))
				return (1);
			rgb = ft_atoi(rgb_values[i]);
			if (0 < rgb || rgb > 255)
				return (1);
			i++;
		}
		free_array(rgb_values);
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
		while (s[i] != 0)
			i++;
		if (i != 6)
			return (1);
		xyz_values = ft_split(s[1], " ");
		i = 0;
		while (xyz_values[i] != NULL)
		{
			if (!ft_isnumeric(xyz_values[i]))
				return (1);
			i++;
		}
		free_array(xyz_values);
		i = 0;
		vector_values = ft_split(s[2], " ");
		while (vector_values[i] != NULL)
		{
			if (!ft_isnumeric(vector_values[i]))
				return (1);
			vector = (float)ft_atoi(vector_values[i]);
			if (-1 < vector || vector > 1)
				return (1);
			i++;
		}
		free_array(vector_values);
		// make sure cylinder diameter is a number
		if (!ft_isnumeric(s[3]))
			return (1);
		if (!ft_isnumeric(s[4]))
			return (1);
		i = 0;
		rgb_values = ft_split(s[5], " ");
		while (rgb_values[i] != NULL)
		{
			if (!ft_isnumeric(rgb_values[i]))
				return (1);
			rgb = ft_atoi(rgb_values[i]);
			if (0 < rgb || rgb > 255)
				return (1);
			i++;
		}
		free_array(rgb_values);
	}
}

int	check_FileContents(t_img *data, int fd)
{
	char	*line;
	char	**str;
	char	*norm_line;

	while ((line = get_next_line(fd)))
	{
		// norm the line and split the line by space
		norm_line = normalize_whitespace(line);
		str = ft_split(norm_line, ' ');
		// run the check functions
	}
}

int	check_FileContents(t_img *data, int fd)
{
	char	*line;
	int		error_flag;

	error_flag = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		// Process each line with the corresponding check function
		if (check_Ambient(data, line) ||
			check_Cam(data, line) || check_Light(data, line) ||
			check_Sp(data, line) || check_Cylinder(data , line))
		{
			error_flag = 1;
			break;
		}
		free(line);
	}
	if (line != NULL)
		free(line);
	printf("error flag : %d\n", error_flag);
	if (!error_flag)
		ft_putstr_fd("Success: All elements have been checked successfully.\n", 1);
	return (error_flag);
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
			return (printf("Error.\nFile provided is not .rt file.\n"));
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (printf("Error.\n The file cannot be opened."));
		// Need to have one function that checks through if the inputs are valid
		// Another function to save the required contents into the struct
		check_FileContents(data, fd);
		free(data);
	}
	else
		return (printf("Error.\nPlease input one .rt file as the argument.\n"));
	return (0);
}
