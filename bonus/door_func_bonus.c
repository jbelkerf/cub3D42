/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_func_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidnassa <aidnassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:29:56 by aidnassa          #+#    #+#             */
/*   Updated: 2025/08/30 16:29:59 by aidnassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

int get_door(t_data *data, int x, int y)
{
    int idx;

    idx = -1;
    while (++idx < data->door_idx)
    {
        int xx = data->doors_info[idx].x;
        int yy = data->doors_info[idx].y;
        if (x == xx && y == yy)
            return (idx);
    }
    return (-1);
    
}

void open_close_door(int idx, t_data *data)
{
    int x;
    int y;
    int i = -1;

    while (++i < data->door_idx)
    {
        x = data->doors_info[i].x;
        y = data->doors_info[i].y;
        if (x != (int) data->player->p_x && y != (int) data->player->p_y)
            data->map[y][x] = 'D';
    }
    x = data->doors_info[idx].x;
    y = data->doors_info[idx].y;
    data->map[y][x] = 'd';
}

void door_func(void *param)
{
    t_data *data;

    data = (t_data *) param;
    if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
    {
        int idx = data->front_door;
        if (idx != -1 && data->doors_info[idx].dist <= 1.0)
        {
            open_close_door(idx, data);
            ft_memset(data->imgs.CUB->pixels, 0, data->imgs.CUB->width * data->imgs.CUB->height * 4);
            raycast(data);
        }
    }
}