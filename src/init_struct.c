/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:19:44 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/04 20:59:36 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_program(t_data *data)
{
	t_prog *prog;

	prog = &data->program;
	prog->mlx_ptr = mlx_init();
	prog->win_ptr = mlx_new_window(prog->mlx_ptr, IMG_WIDTH, IMG_HEIGHT, "MiniRT");
	prog->image = new_img(prog);
	mlx_hook(prog->win_ptr, 17,  0, handle_exit, prog);
	mlx_hook(prog->win_ptr, 2, 1L<<0, handle_keypress, prog);
	mlx_mouse_hook(data->program.win_ptr, handle_mouse_click, prog);
	render_image(prog, data);
	mlx_loop(prog->mlx_ptr);
}

void	init_img_data(t_data *data)
{
	data->error_msg = NULL;
	// ambient
	data->amb_light = 0.5;
	data->amb_rgb.r = 255;
	data->amb_rgb.g = 255;
	data->amb_rgb.b = 255;
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
	// scene
	data->prim_count = 0;
	data->sphere_count = 0;
	data->plane_count = 0;
	data->cylinder_count = 0;
}
