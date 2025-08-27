/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:08:07 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/08/27 22:29:14 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

void	locate_player(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				data->player->p_x = (j + 0.5) * SCALE2D;
				data->player->p_y = (i + 0.5) * SCALE2D;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	is_it_wall(t_data *data, double x, double y)
{
	if (data->map[(int)(y / SCALE2D)][(int)(x / SCALE2D)] == '1')
		return (1);
	return (0);
}

void	move_player(void *param)
{
	t_data	*data;
	double	dx;
	double	dy;

	data = param;
	dx = 0;
	dy = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		mlx_delete_image(data->mlx, data->imgs.CUB);
		data->imgs.CUB = mlx_new_image(data->mlx, data->pxl_width, data->pxl_height);
		mlx_image_to_window(data->mlx, data->imgs.CUB, 0, 0);
		dx = cos(data->player->angle);
		dy = sin(data->player->angle); 
		raycast(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		mlx_delete_image(data->mlx, data->imgs.CUB);
		data->imgs.CUB = mlx_new_image(data->mlx, data->pxl_width, data->pxl_height);
		mlx_image_to_window(data->mlx, data->imgs.CUB, 0, 0);
		dx = cos(data->player->angle + M_PI);
		dy = sin(data->player->angle + M_PI);
		raycast(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		mlx_delete_image(data->mlx, data->imgs.CUB);
		data->imgs.CUB = mlx_new_image(data->mlx, data->pxl_width, data->pxl_height);
		mlx_image_to_window(data->mlx, data->imgs.CUB, 0, 0);
		dx = cos(data->player->angle - (M_PI / 2));
		dy = sin(data->player->angle - (M_PI / 2));
		raycast(data);
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		mlx_delete_image(data->mlx, data->imgs.CUB);
		data->imgs.CUB = mlx_new_image(data->mlx, data->pxl_width, data->pxl_height);
		mlx_image_to_window(data->mlx, data->imgs.CUB, 0, 0);
		dx = cos(data->player->angle + (M_PI / 2));
		dy = sin(data->player->angle + (M_PI / 2));
		raycast(data);
	}
	if ((dx != 0 || dy != 0) && !is_it_wall(data, data->player->p_x + dx + 0.5, data->player->p_y + dy) &&
		!is_it_wall(data, data->player->p_x + dx, data->player->p_y + dy + 0.5) &&
	    !is_it_wall(data, data->player->p_x + dx - 0.5, data->player->p_y + dy) &&
	    !is_it_wall(data, data->player->p_x + dx, data->player->p_y + dy - 0.5))
	{
		data->player->p_x += dx;
		data->player->p_y += dy;
	}
}

void	rotate(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	double	rot_speed;

	data = param;
	rot_speed = 0.07;
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
	{
		mlx_delete_image(data->mlx, data->imgs.CUB);
		data->imgs.CUB = mlx_new_image(data->mlx, data->pxl_width, data->pxl_height);
		mlx_image_to_window(data->mlx, data->imgs.CUB, 0, 0);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		data->player->angle += rot_speed;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
		raycast(data);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		data->player->angle -= rot_speed;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
		raycast(data);
	}
}
