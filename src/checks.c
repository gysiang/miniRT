/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:07:02 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 20:55:56 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_filecontents(t_data *data, int fd)
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
		if (check_ambients(data, split_line) || check_cams(data, split_line)
			|| check_lights(data, split_line) || check_planes(data, split_line)
			|| check_spheres(data, split_line)
			|| check_cylinders(data, split_line))
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
		&& ft_strcmp(s[0], "sp") && ft_strcmp(s[0], "pl")
		&& ft_strcmp(s[0], "cy"))
		return (ft_error("Invalid element"));
	return (0);
}

int	check_capital_elements(t_data *data)
{
	if (data->amb_count != 1 || data->cam_count != 1 || data->light_count > 1)
		return (ft_error("There must be one Ambient and Camera,"
				"and at most one Light"));
	return (0);
}
