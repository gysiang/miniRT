/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:39:14 by bhowe             #+#    #+#             */
/*   Updated: 2024/09/20 13:26:51 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	render_ambient(t_prog *prog, float s, t_rgb *amb)
{
	int	x;
	int	y;
	int	color;

	color = get_rgb((int)(amb->r * s), (int)(amb->g * s), (int)(amb->b * s));
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			set_img_pixel(prog->image, x, y, color);
	}
	mlx_put_image_to_window(prog->mlx_ptr, prog->win_ptr, prog->image->img, 0, 0);
}
