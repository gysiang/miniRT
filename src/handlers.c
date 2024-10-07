/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:16:43 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/07 13:42:02 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_exit(t_data *data)
{
	if (data->program.win_ptr)
	{
		mlx_destroy_window(data->program.mlx_ptr, data->program.win_ptr);
		cleanup(data);
	}
	printf("Successfully exited miniRT.\n");
	exit(0);
}

int handle_keypress(KeySym keysym, t_data *data)
{
	float	speed;
	float	sensitivity;

	speed = 0.1;
	sensitivity = 0.01;
	if (keysym == XK_Escape)
		handle_exit(data);
	else if (keysym == XK_W || keysym == XK_w)
	{
		printf("W key pressed, camera moved forward\n");
		move_camera(&data->camera.position, &data->camera.vector, speed);
		printf("Camera position: (%f, %f, %f)\n", data->camera.position.x, data->camera.position.y, data->camera.position.z);
	}
	else if (keysym == XK_S || keysym == XK_s)
	{
		printf("S key pressed, camera moved backward\n");
		move_camera(&data->camera.position, &data->camera.vector, -speed);
		printf("Camera position: (%f, %f, %f)\n", data->camera.position.x, data->camera.position.y, data->camera.position.z);
	}
	else if (keysym == XK_A || keysym == XK_a)
	{
		printf("A key pressed, camera moved left\n");
		move_camera(&data->camera.position, &data->camera.vector, -speed);
		printf("Camera position: (%f, %f, %f)\n", data->camera.position.x, data->camera.position.y, data->camera.position.z);
	}
	else if (keysym == XK_D || keysym == XK_d)
	{
		printf("D key pressed, camera moved right\n");
		move_camera(&data->camera.position, &data->camera.vector, speed);
		printf("Camera position: (%f, %f, %f)\n", data->camera.position.x, data->camera.position.y, data->camera.position.z);
	}
	else if (keysym == XK_Q || keysym == XK_q)
	{
		printf("Q key pressed, yaw (horizontal) rotation left\n");
		data->camera.yaw -= sensitivity;
		rotate_camera(&data->camera);
		re_render_image(data);
		printf("Camera direction: (%f, %f, %f)\n", data->camera.vector.x, data->camera.vector.y, data->camera.vector.z);
	}
	else if (keysym == XK_E || keysym == XK_e)
	{
		printf("E key pressed, pitch (vertical) rotation up\n");
		data->camera.pitch += sensitivity;
		rotate_camera(&data->camera);
		re_render_image(data);
		printf("Camera direction: (%f, %f, %f)\n", data->camera.vector.x, data->camera.vector.y, data->camera.vector.z);
	}
	return (0);
}

int handle_mouse_click(int button, int x, int y)
{
	if (button == 1)
		printf("Left click at (%d, %d)\n", x, y);
	else if (button == 2)
		printf("Right click at (%d, %d)\n", x, y);
	else if (button == 3)
		printf("Middle click at (%d, %d)\n", x, y);
	else
		printf("Unknown mouse button %d clicked at (%d, %d)\n", button, x, y);
	return (0);
}
