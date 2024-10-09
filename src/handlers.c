/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:16:43 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/09 21:28:57 by gyong-si         ###   ########.fr       */
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

char	*assign_dir(KeySym keysym)
{
	char	*d;

	d = NULL;
	if (keysym == XK_Left)
		d  = "left";
	else if (keysym == XK_Right)
		d = "right";
	else if (keysym == XK_Up)
		d = "up";
	else if (keysym == XK_Down)
		d = "down";
	else if (keysym == XK_W || keysym == XK_w)
		d = "forward";
	else if (keysym == XK_S || keysym == XK_s)
		d = "backward";
	else if (keysym == XK_A || keysym == XK_a)
		d = "left";
	else if (keysym == XK_D || keysym == XK_d)
		d = "right";
	return (d);
}

int	handle_cam_movement(t_data *data, KeySym keysym)
{
	char 		*keyname;
	float		speed;
	t_camera	cam;
	char		*dir;

	speed = 0.1;
	cam = data->camera;
	keyname = XKeysymToString(keysym);
	dir = NULL;
	dir = assign_dir(keysym);
	printf("%s is pressed. Camera moved %s.\n", keyname, dir);
	if (keysym == XK_S || keysym == XK_s || keysym == XK_A || keysym == XK_a)
		speed *= -1;
	data->camera.position = vector_Add(cam.position, vector_Multiply(cam.vector, speed));
	re_render_image(data);
	return (0);
}

int	handle_cam_rotation(t_data *data, KeySym keysym)
{
	float	s;
	char	*keyname;
	char	*dir;

	keyname = XKeysymToString(keysym);
	s = 0.01;
	dir = NULL;
	dir = assign_dir(keysym);
	if (keysym == XK_Left || keysym == XK_Up)
		s *= -1;
	if (keysym == XK_Left)
		data->camera.yaw -= s;
	else if (keysym == XK_Right)
		data->camera.yaw += s;
	else if (keysym == XK_Up)
		data->camera.pitch += s;
	else if (keysym == XK_Down)
		data->camera.pitch -= s;
	printf("%s is pressed. Camera rotate %s.\n", keyname, dir);
	rotate_camera(&data->camera);
	re_render_image(data);
	return (0);
}

int handle_keypress(KeySym keysym, t_data *data)
{
	if (keysym == XK_Escape)
		handle_exit(data);
	else if (keysym == XK_W || keysym == XK_w || keysym == XK_S || keysym == XK_s || keysym == XK_A || keysym == XK_a
		|| keysym == XK_D || keysym == XK_d)
		handle_cam_movement(data, keysym);
	else if (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up || keysym == XK_Down)
		handle_cam_rotation(data, keysym);
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
