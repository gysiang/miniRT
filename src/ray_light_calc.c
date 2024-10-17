/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_light_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:58:49 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/14 12:02:02 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_color(t_data *data, t_rayparams *rp)
{
	rp->amb_fin = rgb_mix(rp->prim_col, rp->amb_def);
	rp->color_fin = rgb_get(rp->amb_fin);
	if (!data->light_count)
		return ;
	if (!in_shadow(data, rp, &data->light))
	{
		rp->light_intensity = calculate_lighting(rp, &data->light);
		rp->diffuse_fin = rgb_mix(rp->prim_col,
				rgb_mul(data->light.rgb, rp->light_intensity));
		rp->color_fin = rgb_get(rgb_add(rp->amb_fin, rp->diffuse_fin));
	}
}
