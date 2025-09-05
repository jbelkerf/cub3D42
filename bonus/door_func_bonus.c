/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_func_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidnassa <aidnassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:29:56 by aidnassa          #+#    #+#             */
/*   Updated: 2025/09/05 11:29:33 by aidnassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

int	get_door(t_data *data, int x, int y)
{
	int	idx;
	int	xx;
	int	yy;

	idx = -1;
	while (++idx <= data->door_idx)
	{
		xx = data->doors_info[idx].x;
		yy = data->doors_info[idx].y;
		if (x == xx && y == yy)
			return (idx);
	}
	return (-1);
}

void	open_door(int idx, t_data *data)
{
	int	x;
	int	y;

	if (idx == -1)
		return ;
	x = data->doors_info[idx].x;
	y = data->doors_info[idx].y;
	if (x != (int)(data->player->p_x / SCALE2D) || y != (int)(data->player->p_y
			/ SCALE2D))
		data->map[y][x] = 'd';
}

void	close_door(t_data *data)
{
	int	i;
	int	dx;
	int	dy;
	int	px;
	int	py;

	i = -1;
	while (++i <= data->door_idx)
	{
		px = (int)(data->player->p_x / SCALE2D);
		py = (int)(data->player->p_y / SCALE2D);
		dx = data->doors_info[i].x;
		dy = data->doors_info[i].y;
		if (px == dx && py == dy)
			return ;
		if (abs(px - dx) > 2 || abs(py - dy) > 2)
			data->map[dy][dx] = 'D';
	}
}

void	set_front_door(t_raycast_md *md)
{
	int	idx;
	int	idx1;

	if (md->raw == WINDOW_X / 2)
	{
		md->data->front_door = -1;
		if (md->data->map[md->cell_y][md->cell_x] == 'D')
		{
			idx = get_door(md->data, md->cell_x, md->cell_y);
			md->data->front_door = idx;
			if (idx == -1)
			{
				idx1 = ++(md->data->door_idx);
				md->data->front_door = idx1;
				md->data->doors_info[idx1].y = md->cell_y;
				md->data->doors_info[idx1].x = md->cell_x;
			}
			if (idx != -1)
				md->data->doors_info[idx].dist = md->dist;
		}
	}
}

void	door_func(void *param)
{
	int		idx;
	t_data	*data;

	data = (t_data *)param;
	close_door(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
	{
		idx = data->front_door;
		if (idx != -1 && data->doors_info[idx].dist <= 1.0
			&& data->doors_info[idx].dist > 0.0)
		{
			open_door(idx, data);
			ft_memset(data->imgs.CUB->pixels, 0, data->imgs.CUB->width
				* data->imgs.CUB->height * 4);
			raycast(data);
		}
	}
}
