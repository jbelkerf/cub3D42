/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:33:28 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/06 11:33:30 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

void	init_stuct(t_render *rn)
{
	rn->start_x = 0;
	rn->start_x = 0;
	rn->end_x = SORD_WIDTH;
	rn->end_y = SORD_HEIGHT;
	rn->x = rn->start_x;
	rn->y = rn->start_y;
}

void	render_gun(t_data *d, mlx_texture_t *txt)
{
	t_render	r;

	init_stuct(&r);
	ft_memset(d->imgs.gun->pixels, 0, SORD_WIDTH * SORD_HEIGHT * 4);
	while (r.x < r.end_x)
	{
		r.y = r.start_y;
		while (r.y < r.end_y)
		{
			if (r.x >= 0 && r.x < WINDOW_X && r.y >= 0 && r.y < WINDOW_Y)
			{
				r.textx = ((r.x - r.start_x) * txt->width) / SORD_WIDTH;
				r.texty = ((r.y - r.start_y) * txt->height) / SORD_HEIGHT;
				r.pxls = &txt->pixels[4 * (r.texty * txt->width + r.textx)];
				if (rgba_to_int(r.pxls) != 0x00000000)
					mlx_put_pixel(d->imgs.gun, r.x, r.y, rgba_to_int(r.pxls));
			}
			r.y++;
		}
		r.x++;
	}
}

void	render_frames(t_data *data, t_frames *f, int type)
{
	int				*count;
	mlx_texture_t	**frames;
	int				max;

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
	if (mlx_get_time() - f->last_time >= FRAME_DELAY)
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
	double	delay;
	double	last_time;

	data = (t_data *)param;
	last_time = data->frames.last_time;
	delay = FRAME_DELAY;
	if (mlx_is_key_down(data->mlx, MLX_KEY_V))
		data->frames.type = AIM;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_F))
		data->frames.type = FIRE;
	if (last_time + delay < mlx_get_time() && data->frames.type == AIM)
	{
		render_frames(data, &data->frames, AIM);
		if (data->frames.aim_count == data->frames.max_aim - 1)
			data->frames.type = 2;
	}
	else if (last_time + delay < mlx_get_time() && data->frames.type == FIRE)
	{
		render_frames(data, &data->frames, FIRE);
		if (data->frames.fire_count == data->frames.max_fire - 1)
			data->frames.type = 2;
	}
}
