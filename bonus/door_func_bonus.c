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

void door_func(void *param)
{
    t_data *data;

    data = (t_data *) param;
    if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
    {
        int x = data->raw.x;
        int y = data->raw.y;
        double dist = data->raw.dist;
        if (data->map[y][x] == 'D' && dist <= 1.0)
        {
            data->map[y][x] = 'd';
            printf("open door\n");
        }
        printf("ray at [%d %d][%c] dist: %f\n", x, y, data->map[y][x], dist);
    }
}