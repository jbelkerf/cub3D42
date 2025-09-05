/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:39:22 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/05 16:08:44 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

void	p2map(mlx_image_t *img, t_render *r, uint32_t color, int scale)
{
	int		x;
	int		y;
	double	center_x;
	double	center_y;

	if (scale != 8)
	{
		center_x = r->x - r->start_x + 1;
		center_y = r->y - r->start_y + 1;
	}
	else
	{
		center_x = r->dx - r->start_x;
		center_y = r->dy - r->start_y;
	}
	x = (center_x * SCALE2D - (SCALE2D / scale));
	y = (center_y * SCALE2D - (SCALE2D / scale));
	while (y < (center_y * SCALE2D + (SCALE2D / scale)) && y < MINI_HEIGHT)
	{
		x = (center_x * SCALE2D - (SCALE2D / scale));
		while (x < (center_x * SCALE2D + (SCALE2D / scale)) && x < MINI_WIDTH)
			mlx_put_pixel(img, x++, y, color);
		y++;
	}
}

void	pre_render_mini(t_render *r, t_data *data)
{
	ft_memset(data->imgs.mini_map->pixels, 0, MINI_WIDTH * MINI_HEIGHT * 4);
	r->start_y = (data->player->p_y / SCALE2D) - (MINI_HEIGHT / SCALE2D / 2);
	if (r->start_y < 0)
		r->start_y = 0;
	r->end_y = (MINI_HEIGHT / SCALE2D) + r->start_y;
	if (r->end_y > data->map_length)
	{
		r->end_y = data->map_length;
		r->start_y = r->end_y - (MINI_HEIGHT / SCALE2D);
		if (r->start_y < 0)
			r->start_y = 0;
	}
	r->start_x = (data->player->p_x / SCALE2D) - (MINI_WIDTH / SCALE2D / 2);
	if (r->start_x < 0)
		r->start_x = 0;
	r->end_x = (MINI_HEIGHT / SCALE2D) + r->start_x;
	if (r->end_x > data->map_width)
	{
		r->end_x = data->map_width;
		r->start_x = r->end_x - (MINI_WIDTH / SCALE2D);
		if (r->start_x < 0)
			r->start_x = 0;
	}
	r->y = r->start_y;
}

void	render_mini_map(t_data *data)
{
	t_render	r;

	pre_render_mini(&r, data);
	while (r.y < r.end_y)
	{
		r.x = r.start_x;
		while (r.x < r.end_x)
		{
			if (data->map[r.y][r.x] == '1')
				p2map(data->imgs.mini_map, &r, 0x00ff00ff, 2);
			else if (ft_strchr("NWES0", data->map[r.y][r.x]))
				p2map(data->imgs.mini_map, &r, 0x0000ffff, 2);
			else if (data->map[r.y][r.x] == 'D')
				p2map(data->imgs.mini_map, &r, 0xffff00ff, 2);
			r.x++;
		}
		r.y++;
	}
	r.dx = (data->player->p_x + (SCALE2D / 2)) / SCALE2D;
	r.dy = (data->player->p_y + (SCALE2D / 2)) / SCALE2D;
	p2map(data->imgs.mini_map, &r, 0xff0000ff, 8);
}
