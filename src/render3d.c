/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:19 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/08/28 14:19:03 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

uint32_t	rgba_to_int(uint8_t *pixels)
{
	return ((uint32_t)(pixels[0] << 24) | (uint32_t)(pixels[1] << 16)
	| (uint32_t)(pixels[2] << 8) | (uint32_t)pixels[3]);
}
struct s_render
{
	int		start;
	int		end;
	int		old_start;
	int		textx;
	int		texty;
	int		wall_height;
	int		y;
	double	wallx;
	double	p_x;
	double	p_y;
	uint8_t	*pixel;
};

void	pre_render(struct s_render *r , double distance, int raw, mlx_texture_t *texture, int side, double ray_angle)
{
	if (raw > WINDOW_X)
		return ;
	r->wall_height = (WINDOW_Y / distance);
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
		r->wallx = (r->p_y / SCALE2D) + (distance * sin(ray_angle));
	else
		r->wallx = (r->p_y / SCALE2D) + (distance * cos(ray_angle));
	r->wallx -= floor(r->wallx);

	r->textx = (int)(r->wallx * (double)texture->width);
	if ((side == 0 && cos(ray_angle) < 0) || (side != 0 && sin(ray_angle) > 0))
		r->textx = texture->width - r->textx - 1;
	r->textx = fmax(0, fmin(r->textx, texture->width - 1));
	r->y = r->start;
}

void render3d(double distance, int raw, mlx_texture_t *texture, t_data *data, int side, double ray_angle)
{
	struct s_render	r;

	r.p_x = data->player->p_x - 0.5;
	r.p_y = data->player->p_y - 0.5;
	pre_render(&r, distance, raw, texture, side, ray_angle);
	while (r.y < r.end)
	{
		if (r.start)
			r.texty = (((r.y - r.start) * texture->height / r.wall_height));
		else
			r.texty = (((r.y - r.old_start) * texture->height / r.wall_height));
		if ((r.texty >= 0 && (uint32_t)r.texty < texture->height && r.y < WINDOW_Y))
		{
			r.pixel = &(texture->pixels[4 * (r.texty * texture->width + r.textx)]);
			mlx_put_pixel(data->imgs.CUB, raw, r.y, rgba_to_int(r.pixel));
		}
		r.y++;
	}
}
