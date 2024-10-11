/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:05:20 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/11 23:51:55 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rgb_get(t_rgb rgb)
{
	return (rgb.r << 16 | rgb.g << 8 | rgb.b);
}

t_rgb	rgb_add(t_rgb x, t_rgb y)
{
	x.r += y.r;
	x.g += y.g;
	x.b += y.b;
	if (x.r > 255)
		x.r = 255;
	if (x.g > 255)
		x.g = 255;
	if (x.b > 255)
		x.b = 255;
	return (x);
}

t_rgb	rgb_mul(t_rgb rgb, float ratio)
{
	rgb.r = (int)(rgb.r * ratio);
	rgb.g = (int)(rgb.g * ratio);
	rgb.b = (int)(rgb.b * ratio);
	if (rgb.r > 255)
		rgb.r = 255;
	if (rgb.g > 255)
		rgb.g = 255;
	if (rgb.b > 255)
		rgb.b = 255;
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
