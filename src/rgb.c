/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:05:20 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/01 12:07:40 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_get(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

t_rgb	rgb_mul(t_rgb rgb, float ratio)
{
	rgb.r = (int)(rgb.r * ratio);
	rgb.g = (int)(rgb.g * ratio);
	rgb.b = (int)(rgb.b * ratio);
	return (rgb);
}

t_rgb	rgb_mix(t_rgb x, t_rgb y)
{
	float	r;
	float	g;
	float	b;

	r = x.r / 255.0;
	g = x.g / 255.0;
	b = x.b / 255.0;
	y.r = (int)y.r * r;
	y.g = (int)y.g * g;
	y.b = (int)y.b * b;
	return (y);
}

t_rgb	rgb_lerp(t_rgb x, t_rgb y, float frac)
{
	t_rgb	res;

	if (x.r == y.r)
		res.r = x.r;
	else
		res.r = x.r + (y.r - x.r) * frac;
	if (x.g == y.g)
		res.g = x.g;
	else
		res.g = x.g + (y.g - x.g) * frac;
	if (x.b == y.b)
		res.b = x.b;
	else
		res.b = x.b + (y.b - x.b) * frac;
	return (res);
}