/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:16:43 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 21:08:15 by gyong-si         ###   ########.fr       */
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
	if (keysym == XK_W || keysym == XK_w || keysym == XK_I
		|| keysym == XK_i)
		d = "forward";
	else if (keysym == XK_S || keysym == XK_s || keysym == XK_K
		|| keysym == XK_k)
		d = "backward";
	else if (keysym == XK_A || keysym == XK_a || keysym == XK_J
		|| keysym == XK_j || keysym == XK_Left)
		d = "left";
	else if (keysym == XK_D || keysym == XK_d || keysym == XK_L
		|| keysym == XK_l || keysym == XK_Right)
		d = "right";
	else if (keysym == XK_Q || keysym == XK_q || keysym == XK_U
		|| keysym == XK_u || keysym == XK_Up)
		d = "up";
	else if (keysym == XK_E || keysym == XK_e || keysym == XK_O
		|| keysym == XK_o || keysym == XK_Down)
		d = "down";
	return (d);
}

int	handle_cam_movement(t_data *data, KeySym keysym)
{
	char	*keyname;
	float	speed;
	char	*dir;

	speed = MV_SPEED;
	keyname = XKeysymToString(keysym);
	dir = NULL;
	dir = assign_dir(keysym);
	if (keysym == XK_S || keysym == XK_s || keysym == XK_A || keysym == XK_a
		|| keysym == XK_E || keysym == XK_e)
		speed *= -1;
	if (keysym == XK_A || keysym == XK_a || keysym == XK_D || keysym == XK_d)
		move_camera(&data->camera.position, speed, LEFTRIGHT);
	else if (keysym == XK_Q || keysym == XK_q || keysym == XK_E
		|| keysym == XK_e)
		move_camera(&data->camera.position, speed, UPDOWN);
	else if (keysym == XK_W || keysym == XK_w || keysym == XK_S
		|| keysym == XK_s)
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

int	handle_light_movement(t_data *data, KeySym keysym)
{
	char		*keyname;
	float		speed;
	char		*dir;

	speed = MV_SPEED;
	keyname = XKeysymToString(keysym);
	dir = NULL;
	dir = assign_dir(keysym);
	if (keysym == XK_K || keysym == XK_k || keysym == XK_J || keysym == XK_j
		|| keysym == XK_U || keysym == XK_u)
		speed *= -1;
	if (keysym == XK_J || keysym == XK_j || keysym == XK_L || keysym == XK_l)
		move_camera(&data->light.position, speed, LEFTRIGHT);
	else if (keysym == XK_U || keysym == XK_u || keysym == XK_O
		|| keysym == XK_o)
		move_camera(&data->light.position, speed, UPDOWN);
	else if (keysym == XK_I || keysym == XK_i || keysym == XK_K
		|| keysym == XK_k)
		move_camera(&data->light.position, speed, FORWARDBACK);
	printf("%s is pressed. Light position moved %s.\n", keyname, dir);
	return (0);
}
