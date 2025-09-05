/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:08:07 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/05 16:12:39 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
			if (ft_strchr("NSEW", map[i][j]))
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

int	is_wall(t_data *data, double dx, double dy)
{
	double	x;
	double	y;

	x = data->player->p_x + dx;
	y = data->player->p_y + dy;
	if (data->map[(int)(y / SCALE2D)][(int)(x / SCALE2D)] == '1')
		return (1);
	return (0);
}

void	help_move(t_data *data, double *dx, double *dy, double angle)
{
	ft_memset(data->imgs.cub->pixels, 0,
		data->imgs.cub->width * data->imgs.cub->height * 4);
	*dx = cos(angle);
	*dy = sin(angle); 
	raycast(data);
}

struct s_move
{
	double	dx;
	double	dy;
};

void	move_player(void *param)
{
	t_data			*data;
	struct s_move	m;

	data = param;
	m.dx = 0;
	m.dy = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		help_move(data, &m.dx, &m.dy, data->player->angle);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		help_move(data, &m.dx, &m.dy, data->player->angle + M_PI);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		help_move(data, &m.dx, &m.dy, data->player->angle - (M_PI / 2));
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		help_move(data, &m.dx, &m.dy, data->player->angle + (M_PI / 2));
	if ((m.dx != 0 || m.dy != 0)
		&& !is_wall(data, m.dx + 0.5, m.dy)
		&& !is_wall(data, m.dx, m.dy + 0.5)
		&& !is_wall(data, m.dx - 0.5, m.dy)
		&& !is_wall(data, m.dx, m.dy - 0.5))
	{
		data->player->p_x += m.dx;
		data->player->p_y += m.dy;
	}
}

void	rotate(void *param)
{
	int		update;
	t_data	*data;

	update = 0;
	data = (t_data *) param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		update = 1;
		data->player->angle += ROTATE_SPEED;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		update = 1;
		data->player->angle -= ROTATE_SPEED;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
	}
	if (update)
	{
		ft_memset(data->imgs.cub->pixels, 0,
			data->imgs.cub->width * data->imgs.cub->height * 4);
		raycast(data);
	}
}
