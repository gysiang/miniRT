/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:16:43 by gyong-si          #+#    #+#             */
/*   Updated: 2024/09/19 13:44:07 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_program(t_prog *prog, t_img *data)
{
	if (prog->win_ptr)
		mlx_destroy_window(prog->mlx_ptr, prog->win_ptr);
	free(data);
	free(prog);
	printf("Successfully exited miniRT.\n");
	exit(0);
}

int handle_keypress(int keycode, t_prog *program, t_img *data)
{
	printf("Key pressed: %d\n", keycode);

	if (keycode == 53 || keycode == 65307) // ESC key
		exit_program(program, data);
	if (keycode == 65362) // Up arrow (MacOS: 126, Linux: 65362)
		printf("Up arrow key pressed\n");
	if (keycode == 65364) // Down arrow (MacOS: 125, Linux: 65364)
		printf("Down arrow key pressed\n");
	if (keycode == 65361) // Left arrow (MacOS: 123, Linux: 65361)
		printf("Left arrow key pressed\n");
	if (keycode == 65363) // Right arrow (MacOS: 124, Linux: 65363)
		printf("Right arrow key pressed\n");
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

int	handle_exit(t_prog *prog, t_img *data)
{
	exit_program(prog, data);
	return (0);
}
