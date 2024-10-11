/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/11 11:21:28 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac == 2)
	{
		if (!check_filetype(av[1]))
			return (ft_error("File provided is not .rt file"));
		if (open_file(&fd, av[1]))
			return (ft_error(".rt file cannot be opened"));
		data = init_data();
		if (check_filecontents(&data, fd))
			return (1);
		printf("Success: All elements have been checked successfully\n");
		close(fd);
		if (open_file(&fd, av[1]))
			return (ft_error(".rt file cannot be opened"));
		if (save_filecontents(&data, fd))
			return (ft_error("Failure saving file contents"));
		printf("Success: All elements have been saved successfully.\n");
		init_program(&data);
	}
	else
		return (ft_error("Please input one .rt file as the argument"));
	return (0);
}
