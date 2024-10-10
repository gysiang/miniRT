/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:07:02 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 14:14:50 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_all_elements(t_data *data, char **s)
{
	return (check_ambient(data, s) || check_cam(data, s)
		|| check_lights(data, s) || check_planes(data, s)
		|| check_spheres(data, s) || check_cylinders(data, s)
		|| check_cones(data, s));
}

int	check_FileContents(t_data *data, int fd)
{
	char	*line;
	char	**split_line;

	while ((line = get_next_line(fd)) != NULL)
	{
		split_line = ft_split(line, " \t\n\v\f\r");
		free(line);
		if (!split_line)
			continue ;
		if (not_element(split_line))
			return (free_array(split_line), 1);
		if (check_all_elements(data, split_line))
			return (free_array(split_line), 1);
		free_array(split_line);
	}
	if (check_capital_elements(data))
		return (1);
	printf("Success: All elements have been checked successfully\n");
	data->prims = malloc(data->prim_count * sizeof(t_prim));
	if (!data->prims)
		return (ft_error("Primitives data failed to initialise"));
	data->prim_count = 0;
	return (0);
}

int	not_element(char **s)
{
	if (ft_strcmp(s[0], "A") && ft_strcmp(s[0], "C") && ft_strcmp(s[0], "L")
		&& ft_strcmp(s[0], "sp") && ft_strcmp(s[0], "pl") && ft_strcmp(s[0], "cy"))
		return (ft_error("Invalid element"));
	return (0);
}

int	check_capital_elements(t_data *data)
{
	if (data->amb_count != 1 || data->cam_count != 1 || data->light_count > 1)
		return (ft_error("There must be one Ambient and Camera, and at most one Light"));
	return (0);
}
