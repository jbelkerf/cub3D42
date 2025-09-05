/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:50:05 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/09/05 12:51:55 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

void	render_gun(t_data *data, mlx_texture_t *txt)
{
	uint8_t	*pixels;
	int		x;
	int		y;

	double start_x, end_x;
	double start_y, end_y;
	int tx, ty;
	ft_memset(data->imgs.gun->pixels, 0, SORD_WIDTH * SORD_HEIGHT * 4);
	start_x = 0;
	start_y = 0;
	end_x = SORD_WIDTH;
	end_y = SORD_HEIGHT;
	x = start_x;
	while (x < end_x)
	{
		y = start_y;
		while (y < end_y)
		{
			if (x >= 0 && x < WINDOW_X && y >= 0 && y < WINDOW_Y)
			{
				tx = ((x - start_x) * txt->width) / SORD_WIDTH;
				ty = ((y - start_y) * txt->height) / SORD_HEIGHT;
				pixels = &txt->pixels[4 * (ty * txt->width + tx)];
				if (rgba_to_int(pixels) != 0x00000000)
					mlx_put_pixel(data->imgs.gun, x, y, rgba_to_int(pixels));
			}
			y++;
		}
		x++;
	}
}

void	render_frames(t_data *data, t_frames *f, int type)
{
	int				*count;
	mlx_texture_t	**frames;
	int				max;

	data->frames.idle = false;
	if (type == AIM)
	{
		count = &f->aim_count;
		frames = f->aim;
		max = f->max_aim;
	}
	else
	{
		count = &f->fire_count;
		frames = f->fire;
		max = f->max_fire;
	}
	if (mlx_get_time() - f->last_time >= 0.1)
	{
		render_gun(data, frames[*count]);
		*count += 1;
		if (*count >= max)
			*count = 0;
		f->last_time = mlx_get_time();
	}
}

void	gun_func(void *param)
{
	t_data	*data;
	int		type;

	data = (t_data *)param;
	type = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_V))
		type = AIM;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_F))
		type = FIRE;
	else
	{
		if (!data->frames.idle && data->frames.last_time + 0.1 < mlx_get_time())
		{
			data->frames.idle = true;
			data->frames.aim_count = 0;
			render_gun(data, data->frames.fire[6]);
		}
	}
}
