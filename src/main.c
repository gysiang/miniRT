/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/17 20:35:47 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		// check if all the elements are present and valid, else return a error message
		check_FileContents(data, fd);
		free(data);
	}
	else
		return (printf("Error.\nPlease input one .rt file as the argument.\n"));
	return (0);
}
