/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:17:46 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 14:17:54 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int save_FileContents(t_data *data, int fd)
{
	char	*line;
	char	**split_line;

	while ((line = get_next_line(fd)) != NULL)
	{
		split_line = ft_split(line, " \t\n\v\f\r");
		free(line);
		if (!split_line)
			continue ;
		if (save_AmbientLight(data, split_line) || save_Camera(data, split_line)
			|| save_Light(data, split_line) || save_sphere(data, split_line)
			|| save_plane(data, split_line) || save_cylicone(data, split_line))
			return (free_array(split_line), 1);
		free_array(split_line);
	}
	printf("Success: All elements have been saved successfully.\n");
	return (0);
}

int	save_RGB(t_rgb *array, char *s)
{
	char	**rgb_values;

	rgb_values = ft_split(s, ",");
	if (!rgb_values)
		return (1);
	array->r = ft_atoi(rgb_values[0]);
	array->g = ft_atoi(rgb_values[1]);
	array->b = ft_atoi(rgb_values[2]);
	free_array(rgb_values);
	return (0);
}

int	save_Vector(t_vec *array, char *s)
{
	char	**vector_values;

	vector_values = ft_split(s, ",");
	if (!vector_values)
		return (1);
	array->x = ft_atof(vector_values[0]);
	array->y = ft_atof(vector_values[1]);
	array->z = ft_atof(vector_values[2]);
	free_array(vector_values);
	return (0);
}




