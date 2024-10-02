/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:16:43 by gyong-si          #+#    #+#             */
/*   Updated: 2024/10/02 14:41:59 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_program(t_prog *prog)
{
	if (prog->win_ptr)
	{
		mlx_destroy_window(prog->mlx_ptr, prog->win_ptr);
		cleanup(prog);
	}
	printf("Successfully exited miniRT.\n");
	exit(0);
}

int handle_keypress(KeySym keysym, t_prog *program)
{
	char	*keyname;

	keyname = XKeysymToString(keysym);
	if (keysym == XK_Escape) // ESC key
		exit_program(program);
	else if (keysym == XK_W || keysym == XK_w) // Up arrow (MacOS: 126, Linux: 65362)
		printf("W key pressed\n");
	else if (keysym == XK_S || keysym == XK_s) // Down arrow (MacOS: 125, Linux: 65364)
		printf("S key pressed\n");
	else if (keysym == XK_A || keysym == XK_a) // Left arrow (MacOS: 123, Linux: 65361)
		printf("A key pressed\n");
	else if (keysym == XK_D || keysym == XK_d) // Right arrow (MacOS: 124, Linux: 65363)
		printf("D key pressed\n");
	else
		printf("Key pressed: %s\n", keyname);
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

int	handle_exit(t_prog *prog)
{
	exit_program(prog);
	return (0);
}
