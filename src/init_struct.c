/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:19:44 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/02 11:15:30 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_test(t_img *data)
{
    t_ray ray;
    float t;  // Use a float for t, not double
    t_vec direction_to_sphere;

    // Initialize t to 0
    t = 0;

    // Calculate ray origin and direction
    ray.origin = data->camera.position;
	direction_to_sphere = vector_Subtract(&data->spheres[0].position, &ray.origin);
    //ray.vector = vector_Normalize(&direction_to_sphere);  // Calculate ray direction towards the sphere
	ray.vector = direction_to_sphere;
    // Check for hit
    if (hit_sphere(&ray, &data->spheres[0], &t))
    {
        printf("Ray hits sphere at t = %f\n", t);  // Dereference t directly, no need for a pointer here
    }
    else
    {
        printf("Ray misses the sphere.\n");
    }
}


void	init_program(t_prog *prog, t_img *data)
{
	prog->mlx_ptr = mlx_init();
	prog->win_ptr = mlx_new_window(prog->mlx_ptr, IMG_WIDTH, IMG_HEIGHT, "MiniRT");
	prog->image = new_img(prog);
	mlx_hook(prog->win_ptr, 17,  0, handle_exit, prog);
	mlx_hook(prog->win_ptr, 2, 1L<<0, handle_keypress, prog);
	mlx_mouse_hook(prog->win_ptr, handle_mouse_click, prog);
	//ray_test(data);
	render_image(prog, data);
	//render_ambient(prog, data->amb_light, &data->amb_rgb);
	mlx_loop(prog->mlx_ptr);
}

void	init_img_data(t_img *data)
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
