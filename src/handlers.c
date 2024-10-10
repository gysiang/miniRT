/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:16:43 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/09 23:28:25 by bhowe            ###   ########.fr       */
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
	else if (keysym == XK_Q || keysym == XK_q)
		d = "up";
	else if (keysym == XK_E || keysym == XK_e)
		d = "down";
	return (d);
}

int	handle_cam_movement(t_data *data, KeySym keysym)
{
	char 		*keyname;
	float		speed;
	char		*dir;

	speed = MV_SPEED;
	keyname = XKeysymToString(keysym);
	dir = NULL;
	dir = assign_dir(keysym);
	if (keysym == XK_S || keysym == XK_s || keysym == XK_A || keysym == XK_a || keysym == XK_E || keysym == XK_e)
		speed *= -1;
	if (keysym == XK_A || keysym == XK_a || keysym == XK_D || keysym == XK_d)
		move_camera(&data->camera.position, speed, LEFTRIGHT);
	else if (keysym == XK_Q || keysym == XK_q || keysym == XK_E || keysym == XK_e)
		move_camera(&data->camera.position, speed, UPDOWN);
	else if (keysym == XK_W || keysym == XK_w || keysym == XK_S || keysym == XK_s)
		move_camera(&data->camera.position, speed, FORWARDBACK);
	printf("%s is pressed. Camera moved %s.\n", keyname, dir);
	return (0);
}

int	handle_cam_rotation(t_data *data, KeySym keysym)
{
	float	s;
	char	*keyname;
	char	*dir;

	keyname = XKeysymToString(keysym);
	s = ROT_SPEED;
	dir = NULL;
	dir = assign_dir(keysym);
	if (keysym == XK_Left || keysym == XK_Down)
		s *= -1;
	if (keysym == XK_Left || keysym == XK_Right)
		data->camera.yaw += s;
	else if (keysym == XK_Up || keysym == XK_Down)
		data->camera.pitch += s;
	rotate_camera(&data->camera);
	printf("%s is pressed. Camera rotate %s.\n", keyname, dir);
	return (0);
}

int handle_keypress(KeySym keysym, t_data *data)
{
	if (keysym == XK_Escape)
		handle_exit(data);
	else if (keysym == XK_W || keysym == XK_w || keysym == XK_S || keysym == XK_s || keysym == XK_A || keysym == XK_a
		|| keysym == XK_D || keysym == XK_d || keysym == XK_Q || keysym == XK_q || keysym == XK_E || keysym == XK_e)
		handle_cam_movement(data, keysym);
	else if (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up || keysym == XK_Down)
		handle_cam_rotation(data, keysym);
	re_render_image(data);
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
