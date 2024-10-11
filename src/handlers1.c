/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:07:42 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/10 21:08:19 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_keypress(KeySym keysym, t_data *data)
{
	if (keysym == XK_Escape)
		handle_exit(data);
	else if (keysym == XK_W || keysym == XK_w || keysym == XK_S
		|| keysym == XK_s || keysym == XK_A || keysym == XK_a || keysym == XK_D
		|| keysym == XK_d || keysym == XK_Q || keysym == XK_q || keysym == XK_E
		|| keysym == XK_e)
		handle_cam_movement(data, keysym);
	else if (keysym == XK_Left || keysym == XK_Right || keysym == XK_Up
		|| keysym == XK_Down)
		handle_cam_rotation(data, keysym);
	else if (keysym == XK_I || keysym == XK_i || keysym == XK_K
		|| keysym == XK_k || keysym == XK_J || keysym == XK_j || keysym == XK_L
		|| keysym == XK_l || keysym == XK_U || keysym == XK_u || keysym == XK_o
		|| keysym == XK_O)
		handle_light_movement(data, keysym);
	re_render_image(data);
	return (0);
}

int	handle_mouse_click(int button, int x, int y)
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
