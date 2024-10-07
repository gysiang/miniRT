/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:14:34 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/07 10:20:49 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *  Upates the camera position based on wasd
 */

void move_camera(t_vec *pos, t_vec *direction, float speed)
{
	pos->x += direction->x * speed;
	pos->y += direction->y * speed;
	pos->z += direction->z * speed;
}

void	rotate_camera(t_camera *camera)
{
	t_vec new_direction;

	new_direction.x = cos(camera->pitch) * sin(camera->yaw);
	new_direction.y = sin(camera->pitch);
	new_direction.z = cos(camera->pitch) * cos(camera->yaw);
	new_direction = vector_Normalize(&new_direction);
	camera->vector = new_direction;
}

void	re_render_image(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;
	t_prog	prog;

	prog = data->program;
	mlx_clear_window(data->program.mlx_ptr, data->program.win_ptr);

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
	mlx_put_image_to_window(prog.mlx_ptr, prog.win_ptr, prog.image->img, 0, 0);
}
