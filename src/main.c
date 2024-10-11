/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 21:45:10 by gyong-si         ###   ########.fr       */
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
		close(fd);
		if (open_file(&fd, av[1]))
			return (ft_error(".rt file cannot be opened"));
		if (save_filecontents(&data, fd))
			return (ft_error("Failure saving file contents"));
		init_program(&data);
	}
	else
		return (ft_error("Please input one .rt file as the argument"));
	return (0);
}
