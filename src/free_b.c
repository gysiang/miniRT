/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:27:31 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/15 15:04:43 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	cleanup(t_data *data)
{
	del_img(&data->program, data->program.image);
	mlx_destroy_display(data->program.mlx_ptr);
	free(data->prims);
	if (data->light_arr)
		free(data->light_arr);
	free(data->program.mlx_ptr);
}
