/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:19:44 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/17 17:20:14 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_img_data(t_img *data)
{
	// ambient
	data->amb_light = 0;
	data->amb_rgb.r = 0;
	data->amb_rgb.g = 0;
	data->amb_rgb.b = 0;
	// camera
	data->camera.position.x = 0;
	data->camera.position.y = 0;
	data->camera.position.z = 0;
	data->camera.vector.x = 0;
	data->camera.vector.y = 0;
	data->camera.vector.z = 0;
	data->camera.fov = 0;
	// light (no rgb)
	data->light.position.x = 0;
	data->light.position.y = 0;
	data->light.position.z = 0;
	data->light.brightness = 0.0;
	// sphere
	data->sphere.position.x = 0;
	data->sphere.position.x = 0;
	data->sphere.position.x = 0;
	data->sphere.diameter = 0;
	data->sphere.rgb.r = 0;
	data->sphere.rgb.g = 0;
	data->sphere.rgb.b = 0;
	// plane
	data->plane.position.x = 0;
	data->plane.position.y = 0;
	data->plane.position.z = 0;
	data->plane.vector.x = 0;
	data->plane.vector.y = 0;
	data->plane.vector.z = 0;
	data->plane.rgb.r = 0;
	data->plane.rgb.g = 0;
	data->plane.rgb.b = 0;
	// cylinder
	data->cylinder.position.x = 0;
	data->cylinder.position.y = 0;
	data->cylinder.position.z = 0;
	data->cylinder.vector.x = 0;
	data->cylinder.vector.y = 0;
	data->cylinder.vector.z = 0;
	data->cylinder.diameter = 0.0;
	data->cylinder.height = 0.00;
	data->cylinder.rgb.r = 0;
	data->cylinder.rgb.g = 0;
	data->cylinder.rgb.b = 0;
}