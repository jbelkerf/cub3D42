/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:19 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/05 15:20:58 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

uint32_t	rgba_to_int(uint8_t *pixels)
{
	return ((uint32_t)(pixels[0] << 24) | (uint32_t)(pixels[1] << 16)
	| (uint32_t)(pixels[2] << 8) | (uint32_t)pixels[3]);
}

typedef struct s_render_two
{
	int		start;
	int		end;
	int		old_strt;
	int		textx;
	int		texty;
	int		wall_height;
	int		y;
	double	wallx;
	uint8_t	*pixel;
	uint8_t	*pxls;
}	t_render_two;

void	pre_render(t_render_two *r, t_raycast_md *md)
{
	r->wall_height = (WINDOW_Y / md->dist);
	r->start = (WINDOW_Y / 2) - (r->wall_height / 2);
	r->end = (WINDOW_Y / 2) + (r->wall_height / 2);
	r->old_strt = 0;
	if (r->start < 0)
	{
		r->old_strt = r->start;
		r->start = 0;
	}
	if (r->end > WINDOW_Y)
		r->end = WINDOW_Y;
	if (!md->side)
		r->wallx = ((md->data->player->p_y - 0.5) / SCALE2D)
			+ (md->dist * sin(md->ray_angle));
	else
		r->wallx = ((md->data->player->p_x - 0.5) / SCALE2D)
			+ (md->dist * cos(md->ray_angle));
	r->wallx -= floor(r->wallx);
	r->textx = (int)(r->wallx * (double)md->texture->width);
	if ((md->side == 0 && cos(md->ray_angle) < 0)
		|| (md->side != 0 && sin(md->ray_angle) > 0))
		r->textx = md->texture->width - r->textx - 1;
	r->textx = fmax(0, fmin(r->textx, md->texture->width - 1));
	r->y = r->start;
}

void	render3d(t_raycast_md *m)
{
	t_render_two	r;

	if (m->raw > WINDOW_X)
		return ;
	r.pxls = m->texture->pixels;
	pre_render(&r, m);
	while (r.y < r.end)
	{
		if (r.y < MINI_HEIGHT && m->raw < MINI_WIDTH)
		{
			r.y++;
			continue ;
		}
		if (r.start)
			r.texty = (((r.y - r.start) * m->texture->height / r.wall_height));
		else
			r.texty = ((r.y - r.old_strt) * m->texture->height / r.wall_height);
		if ((r.texty >= 0 && (uint32_t)r.texty < m->texture->height
				&& r.y < WINDOW_Y))
		{
			r.pixel = &(r.pxls[4 * (r.texty * m->texture->width + r.textx)]);
			mlx_put_pixel(m->data->imgs.CUB, m->raw, r.y, rgba_to_int(r.pixel));
		}
		r.y++;
	}
}
