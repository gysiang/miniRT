/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_light_calc_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:58:49 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/15 15:27:33 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	add_lighting(t_rayparams *rp, t_light *l)
{
	t_rgb	white;

	white.r = 255;
	white.g = 255;
	white.b = 255;
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

float	get_specular(t_rayparams *rp, t_light *l)
{
	t_vec	light_vec;
	t_vec	half;
	float	spec_intensity;

	light_vec = vector_normalize(vector_subtract(l->position, rp->t_hitpoint));
	half = vector_normalize(vector_add(light_vec, rp->view_vec));
	spec_intensity = vector_dotproduct(rp->t_normal, half);
	spec_intensity /= vector_dotproduct(rp->t_normal, rp->t_normal);
	return (spec_intensity);
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
	if (!rp->in_shadow)
		rp->color_fin = rgb_get(rgb_add(rp->amb_fin, rp->diffuse_fin));
	else
		rp->color_fin = rgb_get(rp->diffuse_fin);
}
