/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_func_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:32:54 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/06 11:32:57 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

static void	do_cursor_rotate(t_data *data, double delta_x)
{
	double	speed;

	speed = 0.003;
	data->player->angle += delta_x * speed;
	if (data->player->angle < 0)
		data->player->angle += 2 * M_PI;
	if (data->player->angle >= 2 * M_PI)
		data->player->angle -= 2 * M_PI;
	ft_memset(data->imgs.cub->pixels, 0, data->imgs.cub->width
		* data->imgs.cub->height * 4);
	data->mouse_ignore_next = 1;
	mlx_set_mouse_pos(data->mlx, WINDOW_X / 2, WINDOW_Y / 2);
	raycast(data);
}

static void	cursor_rotate(t_data *data, double xpos)
{
	double	delta_x;

	if (data->mouse_ignore_next)
	{
		data->mouse_ignore_next = 0;
		data->mouse_last_x = xpos;
		return ;
	}
	if (data->mouse_last_x == -1)
	{
		data->mouse_last_x = xpos;
		return ;
	}
	delta_x = xpos - data->mouse_last_x;
	if (fabs(delta_x) > 0.1)
		do_cursor_rotate(data, delta_x);
	data->mouse_last_x = xpos;
}

void	cursor_func(double xpos, double ypos, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (xpos > WINDOW_X || xpos < 0 || ypos > WINDOW_Y || ypos < 0)
		return ;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	cursor_rotate(data, xpos);
}
