/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:07:02 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/11 16:06:36 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_elements(t_data *data, char **s)
{
	return (check_ambients(data, s) || check_cams(data, s)
		|| check_lights(data, s) || check_planes(data, s)
		|| check_spheres(data, s)
		|| check_cylinders(data, s));
}

int	check_filecontents(t_data *data, int fd)
{
	char	*line;
	char	**split_line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split_line = ft_split(line, " \t\n\v\f\r");
		free(line);
		if (!split_line)
			continue ;
		if (not_element(split_line))
			return (free_array(split_line), 1);
		if (check_elements(data, split_line))
			return (free_array(split_line), 1);
		free_array(split_line);
	}
	if (check_capital_elements(data))
		return (1);
	if (setup_elem_data(data))
		return (ft_error("Primitives data failed to initialise"));
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
