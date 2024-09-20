/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/19 19:18:03 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_FileContents(t_img *data, int fd)
{
	char	*line;
	char	*norm_line;
	char	**split_line;
	int		error_flag;

	error_flag = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		norm_line = normalize_whitespace(line);
		split_line = ft_split(norm_line, ' ');
		if (check_Ambients(data, split_line) || check_Cams(data, split_line) ||
			check_Lights(data, split_line) || check_Planes(data, split_line)  ||
			check_Spheres(data, split_line) || check_Cylinders(data , split_line))
		{
			error_flag = 1;
			break;
		}
		free(line);
	}
	if (line != NULL)
	{
		free(line);
		free_array(split_line);
	}
	if (error_flag)
		printf("%s",data->error_msg);
	else
		printf("Success: All elements have been checked successfully.\n");
	return (error_flag);
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
			return (printf("Error.\n Image data failed to initalise."));
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
		// Save the img data into struct
		init_program(program);
	}
	else
		return (printf("Error.\nPlease input one .rt file as the argument.\n"));
	return (0);
}
