/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:39:14 by bhowe             #+#    #+#             */
/*   Updated: 2024/09/30 16:47:13 by bhowe            ###   ########.fr       */
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
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
			set_img_pixel(prog->image, x, y, color);
	}
	mlx_put_image_to_window(prog->mlx_ptr, prog->win_ptr, prog->image->img, 0, 0);
}

/**
 * Draw the radius to the image
 */
void draw_sphere_projection(t_prog *prog, t_sphere *sphere)
{
    // Project the sphere center onto the 2D image plane
    int screen_x = (int)((sphere->position.x / sphere->position.z) * IMG_WIDTH / 2 + IMG_WIDTH / 2);
    int screen_y = (int)((sphere->position.y / sphere->position.z) * IMG_HEIGHT / 2 + IMG_HEIGHT / 2);

    // The size of the projected radius depends on how far the sphere is from the camera
    int projected_radius = (int)((sphere->radius / sphere->position.z) * IMG_WIDTH / 2);
	printf("radius: %d\n",projected_radius);
    // Draw a simple 2D circle on the screen
    for (int y = -projected_radius; y <= projected_radius; y++) {
        for (int x = -projected_radius; x <= projected_radius; x++) {
            if (x*x + y*y <= projected_radius * projected_radius) {
                set_img_pixel(prog->image, screen_x + x, screen_y + y, get_rgb(sphere->rgb.r, sphere->rgb.g, sphere->rgb.b));
            }
        }
    }
}

void	render_image(t_prog *prog, t_img *data)
{
	int		x;
	int		y;
	t_ray	ray;
	int		color;

	y = -1;
	printf("Camera position: (%f, %f, %f)\n", data->camera.position.x, data->camera.position.y, data->camera.position.z);
	printf("Camera vector: (%f, %f, %f)\n", data->camera.vector.x, data->camera.vector.y, data->camera.vector.z);
	printf("Sphere position: (%f, %f, %f)\n", data->spheres[0].position.x, data->spheres[0].position.y, data->spheres[0].position.z);
	printf("Sphere size: %f\n", data->spheres[0].diameter);

	while (y++ < IMG_HEIGHT)
	{
		x = -1;
		while (x++ < IMG_WIDTH)
		{
			// get the ray direction
			ray = make_ray(data, x, y);
			// trace the ray to see if it hits the obj else it will return the ambient color
			color = trace_ray(&ray, data);
			//draw_sphere_projection(prog, &data->spheres[0]);
			set_img_pixel(prog->image, x, y, color);
		}
	}
	mlx_put_image_to_window(prog->mlx_ptr, prog->win_ptr, prog->image->img, 0, 0);
}
