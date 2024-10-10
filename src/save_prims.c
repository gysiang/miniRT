/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_prims.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:05:57 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 14:21:40 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	save_sphere(t_data *data, char **s)
{
	t_sphere	sp;

	if (ft_strcmp(s[0], "sp") == 0)
	{
		sp.radius = ft_atof(s[2]) / 2;
		data->prims[data->prim_count].p_data.sp = sp;
		save_RGB(&data->prims[data->prim_count].rgb, s[3]);
		save_Vector(&data->prims[data->prim_count].position, s[1]);
		data->prims[data->prim_count].p_type = SP;
		data->prim_count++;
	}
	return (0);
}

int	save_plane(t_data *data, char **s)
{
	if (ft_strcmp(s[0], "pl") == 0)
	{
		save_Vector(&data->prims[data->prim_count].position, s[1]);
		save_Vector(&data->prims[data->prim_count].vector, s[2]);
		data->prims[data->prim_count].vector = \
			vector_Normalize(data->prims[data->prim_count].vector);
		save_RGB(&data->prims[data->prim_count].rgb, s[3]);
		data->prims[data->prim_count].p_type = PL;
		data->prim_count++;
	}
	return (0);
}

int	save_cylicone(t_data *data, char **s)
{
	t_cylicone	cyn;
	bool		cy;
	bool		cn;

	cy = !ft_strcmp(s[0], "cy");
	cn = !ft_strcmp(s[0], "cn");
	if (cy || cn)
	{
		cyn.radius = ft_atof(s[3]) / 2;
		cyn.height = ft_atof(s[4]);
		data->prims[data->prim_count].p_data.cyn = cyn;
		save_Vector(&data->prims[data->prim_count].position, s[1]);
		save_Vector(&data->prims[data->prim_count].vector, s[2]);
		data->prims[data->prim_count].vector = \
			vector_Normalize(data->prims[data->prim_count].vector);
		save_RGB(&data->prims[data->prim_count].rgb, s[5]);
		if (cy)
			data->prims[data->prim_count].p_type = CY;
		else
			data->prims[data->prim_count].p_type = CN;
		data->prim_count++;
	}
	return (0);
}


