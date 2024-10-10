/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:39:14 by bhowe             #+#    #+#             */
/*   Updated: 2024/10/10 21:31:03 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_image(t_data *data)
{
	int		x;
	int		y;
	int		color;
	t_ray	ray;
	t_prog	prog;

	prog = data->program;
	y = -1;
	while (y++ < IMG_HEIGHT)
	{
		x = -1;
		while (x++ < IMG_WIDTH)
		{
			ray = make_ray(data, x, y);
			color = trace_ray(&ray, data);
			set_img_pixel(prog.image, x, y, color);
		}
	}
	mlx_put_image_to_window(prog.mlx_ptr, prog.win_ptr,
		prog.image->img, 0, 0);
}

void	re_render_image(t_data *data)
{
	mlx_clear_window(data->program.mlx_ptr, data->program.win_ptr);
	render_image(data);
}
