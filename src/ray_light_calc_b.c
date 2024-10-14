/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_lighting_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:58:49 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/14 12:01:23 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	add_lighting(t_rayparams *rp, t_light *l)
{
	rp->light_intensity = calculate_lighting(rp, l);
	rp->color_temp = rgb_mix(rp->prim_col,
			rgb_mul(l->rgb, rp->light_intensity));
	if (rp->first_light_calc)
	{
		rp->first_light_calc = false;
		return (rp->color_temp);
	}
	return (rgb_add(rp->diffuse_fin, rp->color_temp));
}

t_rgb	add_shadow(t_rayparams *rp)
{
	if (rp->first_light_calc)
	{
		rp->first_light_calc = false;
		return (rp->amb_fin);
	}
	return (rgb_mix(rp->diffuse_fin, rp->amb_fin));
}

void	calc_color(t_data *data, t_rayparams *rp)
{
	int		i;

	rp->amb_fin = rgb_mix(rp->prim_col, rp->amb_def);
	rp->color_fin = rgb_get(rp->amb_fin);
	if (!data->light_count)
		return ;
	i = -1;
	while (++i < data->light_count)
	{
		if (!in_shadow(data, rp, &data->light_arr[i]))
			rp->diffuse_fin = add_lighting(rp, &data->light_arr[i]);
		else
			rp->diffuse_fin = add_shadow(rp);
	}
	rp->color_fin = rgb_get(rgb_add(rp->amb_fin, rp->diffuse_fin));
}
