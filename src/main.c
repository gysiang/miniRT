/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:16:06 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/19 09:57:09 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/** *
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
} **/

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

void	exit_program(t_img *data)
{
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

int	handle_exit(t_img *data)
{
	exit_program(data);
	return (0);
}

void	init_image(t_img *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "MiniRT");
	mlx_hook(data->win_ptr, 17,  0, handle_exit, data);
	mlx_loop(data->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_img	*data;
	int		i;
	int		fd;

	if (ac == 2)
	{
		data = malloc(sizeof(*data));
		if (!data)
			return (printf("Error.\n Image failed to initalise."));
		init_img_data(data);
		i = checkfiletype(av[1]);
		if (!i)
			return (printf("Error.\nFile provided is not .rt file.\n"));
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (printf("Error.\nThe file cannot be opened."));
		// Need to have one function that checks through if the inputs are valid
		check_FileContents(data, fd);
		init_image(data);
	}
	else
		return (printf("Error.\nPlease input one .rt file as the argument.\n"));
	return (0);
}
