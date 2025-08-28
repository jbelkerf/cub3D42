/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:15:31 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/28 15:01:28 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"


void	init_md(t_raycast_md *md, t_data *data)
{
	md->delta_x = INFINITY;
	md->delta_y = INFINITY;
	md->player_x = (data->player->p_x - 0.5) / SCALE2D;
	md->player_y = (data->player->p_y - 0.5) / SCALE2D;
	md->data = data;
}

void	raycast(t_data *data)
{
	t_raycast_md md;
	double	angle;
	
	ft_memset(&md, 0, sizeof(t_raycast_md));
	init_md(&md, data);
	angle = data->player->angle;
	md.ray_angle = angle - ((FOV * M_PI / 180) / 2);
	while (md.raw < WINDOW_X)
	{
		md.cell_x = (int)(md.player_x);
		md.cell_y = (int)(md.player_y);
		md.ray_dx = cos(md.ray_angle);
		md.ray_dy = sin(md.ray_angle);
		md.step_x = 1;
		md.step_y = 1;
		if (md.ray_dx < 0)
			md.step_x = -1;
		if (md.ray_dy < 0)
			md.step_y = -1;
		if (md.ray_dx != 0)
			md.delta_x = fabs(1.0 / md.ray_dx);
		if (md.ray_dy != 0)
			md.delta_y = fabs(1.0 / md.ray_dy);
		if (md.ray_dx < 0)
			md.side_x = (md.player_x - md.cell_x) * md.delta_x;
		else
			md.side_x = (md.cell_x + 1.0 - md.player_x) * md.delta_x;
		if (md.ray_dy < 0)
			md.side_y = (md.player_y - md.cell_y) * md.delta_y;
		else
			md.side_y = (md.cell_y + 1.0 - md.player_y) * md.delta_y;
		int hit = 0;
		
		while (hit == 0)
		{
			if (md.side_x < md.side_y)
			{
				md.side_x += md.delta_x;
				md.cell_x += md.step_x;
				md.side = 0;
			}
			else
			{
				md.side_y += md.delta_y;
				md.cell_y += md.step_y;
				md.side = 1;
			}
			if (data->map[md.cell_y][md.cell_x] == '1')
				hit = 1;
		}

		if (md.side == 0)
			md.dist = (md.cell_x - md.player_x + (1 - md.step_x) / 2) / md.ray_dx;
		else
			md.dist = (md.cell_y - md.player_y + (1 - md.step_y) / 2) / md.ray_dy;

		if (md.side)
		{
			if (md.ray_dy > 0)
				md.texture = data->texts.north;
			else
				md.texture = data->texts.south;
		}
		else
		{
			if (md.ray_dx > 0)
				md.texture = data->texts.east;
			else
				md.texture = data->texts.west;
		}
		md.dist *= cos(angle - md.ray_angle);
		if (md.dist < 0)
			md.dist = 0;
		render3d(md.dist, md.raw, md.texture, md.data, md.side, md.ray_angle);
		md.ray_angle += (FOV * M_PI / 180) / WINDOW_X;
		md.raw++;
	}
}
