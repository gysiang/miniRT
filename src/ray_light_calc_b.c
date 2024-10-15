/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_light_calc_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:58:49 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/15 17:00:20 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		if (in_shadow(data, rp, &data->light_arr[i]))
			continue ;
		rp->diffuse_fin = add_lighting(rp, &data->light_arr[i]);
		rp->diffuse_fin = rgb_add(rp->diffuse_fin,
						get_specular(rp, &data->light_arr[i]));
	}
	rp->color_fin = rgb_get(rgb_add(rp->amb_fin, rp->diffuse_fin));
}

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

t_rgb	get_specular(t_rayparams *rp, t_light *l)
{
	t_vec	light_vec;
	t_vec	reflect_vec;
	float	spec_intensity;

	light_vec = vector_normalize(vector_subtract(l->position, rp->t_hitpoint));
	reflect_vec = vector_subtract(vector_multiply(rp->t_normal, 2 * vector_dotproduct(rp->t_normal, light_vec)), light_vec);
	spec_intensity = pow(fmax(vector_dotproduct(reflect_vec, rp->view_vec), EPSILON), 200);
	return (rgb_mul(l->rgb, spec_intensity));
}
