/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:49:30 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/11 17:33:58 by JbelkerfIse      ###   ########.fr       */
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
			if (map[i][j] == 'N')
			{
				data->player->p_x = j * SCALE2D;
				data->player->p_y = i * SCALE2D;
				break ;
			}
			j++;
		}
		i++;
	}
	data->player->angle = 0;
}


unsigned	get_color(int *cols)
{
	return (cols[0] << 24 | cols[1] << 16 | cols[2] << 8 | VISIBILTY);
}

void rnder_floor_and_ceil(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < (data->pixel_height / 8))
	{
		x = 0;
		while (x < data->pixel_width)
		{
			mlx_put_pixel(data->imgs.C3D, x, y, get_color(data->ceil_rgb));
			// printf("1\n");
			x += 1;
		}
		y += 1;
	}
	y = (data->pixel_height / 8) * 7;
	while (y < data->pixel_height)
	{
		x = 0;
		while (x < data->pixel_width)
		{
			mlx_put_pixel(data->imgs.C3D, x, y,  get_color(data->floor_rgb));
			x += 1;
		}
		y += 1;
	}
	
}

void	get_images(t_data *data)
{
	mlx_image_t	*img;

	data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
	mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
	rnder_floor_and_ceil(data);
	img = create_render(data->mlx, floor_texture, '0', data->map);
	data->imgs.floor = img;
	img = create_render(data->mlx, wall_texture, '1', data->map);
	data->imgs.wall = img;
	img = create_render(data->mlx, player_texture, 'N', data->map);
	data->imgs.player = img;
	data->imgs.ray = mlx_new_image(data->mlx, data->map_width * SCALE2D, data->map_length * SCALE2D);
	mlx_image_to_window(data->mlx, data->imgs.ray, 0 , 0);
	raycast(data);
}

void move_player(void *param)
{
	t_data * data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if(mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		double dx = cos(data->player->angle * M_PI / 180.0);
		double dy = sin(data->player->angle * M_PI / 180.0);
		data->imgs.player->instances[0].y += 2 * dy;
		data->imgs.player->instances[0].x += 2 * dx;
		raycast(data);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->imgs.player->instances[0].y += MOVE_PIX;
		data->player->p_y += MOVE_PIX;
		raycast(data);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		data->imgs.player->instances[0].x -= MOVE_PIX;
		data->player->p_x -= MOVE_PIX;
		raycast(data);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		data->imgs.player->instances[0].x += MOVE_PIX;
		data->player->p_x += MOVE_PIX;
		raycast(data);
	}
}


void rotate(mlx_key_data_t keydata, void *param)
{
	t_data *data;
	
	data = param;
	if (keydata.key == MLX_KEY_RIGHT)
	{
		// printf("right\n");
		data->player->angle = fmod(data->player->angle + ROTATE_DEG, 360.0);
		raycast(data);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		// printf("lft\n");
		data->player->angle = fmod(data->player->angle - ROTATE_DEG + 360.0, 360.0);
		raycast(data);
	}
}

void set_data(t_data *data)
{
	locate_player(data, data->map);
	data->map_width -= 1;
	data->pixel_width = data->map_width * SCALE2D * SCALE3D;
	data->pixel_height =  data->map_length * SCALE2D * SCALE3D;
}

int	main(int ac, char **av)
{
	t_data	data;
	t_player player;

	if (ac != 2)
		put_error("Usage: ./cube <map_file>");
	data.player = &player;
	check_map_validity(av[1]);
	fill_the_data(&data, av[1]);
	set_data(&data);
	data.mlx = mlx_init(data.pixel_width, data.pixel_height, "cub3D", false);
	if (!data.mlx)
	{
		free_arr(data.map);
		put_error("mlx_init error");
	}
	get_images(&data);
	mlx_loop_hook(data.mlx, move_player, (void *)&data);
	mlx_key_hook(data.mlx, rotate, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}
