/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:19 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/08/28 14:59:42 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

uint32_t	rgba_to_int(uint8_t *pixels)
{
	return ((uint32_t)(pixels[0] << 24) | (uint32_t)(pixels[1] << 16)
	| (uint32_t)(pixels[2] << 8) | (uint32_t)pixels[3]);
}

typedef struct s_render
{
	int		start;
	int		end;
	int		old_start;
	int		textx;
	int		texty;
	int		wall_height;
	int		y;
	double	wallx;
	uint8_t	*pixel;
	uint8_t	*pxls;
}	t_render;

void	pre_render(t_render *r , double dst, mlx_texture_t *texture, t_data *data, int side, double r_angl)
{
	r->wall_height = (WINDOW_Y / dst);
	r->start = (WINDOW_Y / 2) - (r->wall_height / 2);
	r->end = (WINDOW_Y / 2) + (r->wall_height / 2);
	r->old_start = 0;
	if (r->start < 0)
	{
		r->old_start = r->start;
		r->start = 0;
	}
	if (r->end > WINDOW_Y)
		r->end = WINDOW_Y;
	if (!side)
		r->wallx = ((data->player->p_y - 0.5) / SCALE2D) + (dst * sin(r_angl));
	else
		r->wallx = ((data->player->p_x - 0.5) / SCALE2D) + (dst * cos(r_angl));
	r->wallx -= floor(r->wallx);

	r->textx = (int)(r->wallx * (double)texture->width);
	if ((side == 0 && cos(r_angl) < 0) || (side != 0 && sin(r_angl) > 0))
		r->textx = texture->width - r->textx - 1;
	r->textx = fmax(0, fmin(r->textx, texture->width - 1));
	r->y = r->start;
}

void render3d(double distance, int raw, mlx_texture_t *texture, t_data *data, int side, double ray_angle)
{
	t_render	r;


	if (raw > WINDOW_X)
		return ;
	r.pxls = texture->pixels;
	pre_render(&r, distance, texture, data, side, ray_angle);
	while (r.y < r.end)
	{
		if (r.start)
			r.texty = (((r.y - r.start) * texture->height / r.wall_height));
		else
			r.texty = (((r.y - r.old_start) * texture->height / r.wall_height));
		if ((r.texty >= 0 && (uint32_t)r.texty < texture->height
				&& r.y < WINDOW_Y))
		{
			r.pixel = &(r.pxls[4 * (r.texty * texture->width + r.textx)]);
			mlx_put_pixel(data->imgs.CUB, raw, r.y, rgba_to_int(r.pixel));
		}
		r.y++;
	}
}
