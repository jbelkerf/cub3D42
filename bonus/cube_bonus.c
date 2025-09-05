/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:49:30 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/09/05 15:41:08 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

unsigned int	g_clr(int *cols)
{
	return (cols[0] << 24 | cols[1] << 16 | cols[2] << 8 | VISIBILTY);
}

void	rnder_floor_and_ceil(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->pxl_height / 2)
	{
		x = 0;
		while (x < data->pxl_width)
		{
			mlx_put_pixel(data->imgs.background, x, y, g_clr(data->ceil_rgb));
			x += 1;
		}
		y += 1;
	}
	y = data->pxl_height / 2;
	while (y < data->pxl_height)
	{
		x = 0;
		while (x < data->pxl_width)
		{
			mlx_put_pixel(data->imgs.background, x, y, g_clr(data->floor_rgb));
			x += 1;
		}
		y += 1;
	}
}

void	get_images(t_data *data)
{
	mlx_image_t	*tmp;

	tmp = mlx_new_image(data->mlx, data->pxl_width, data->pxl_height);
	data->imgs.background = tmp;
	mlx_image_to_window(data->mlx, data->imgs.background, 0, 0);
	tmp = mlx_new_image(data->mlx, data->pxl_width, data->pxl_height);
	data->imgs.CUB = tmp;
	mlx_image_to_window(data->mlx, data->imgs.CUB, 0, 0);
	rnder_floor_and_ceil(data);
	tmp = mlx_new_image(data->mlx, MINI_WIDTH * SCALE2D, MINI_HEIGHT * SCALE2D);
	data->imgs.ray = tmp;
	mlx_image_to_window(data->mlx, data->imgs.ray, 0, 0);
	data->imgs.gun = mlx_new_image(data->mlx, SORD_WIDTH, SORD_HEIGHT);
	mlx_image_to_window(data->mlx, data->imgs.gun, WINDOW_X - (SORD_WIDTH * 2),
		WINDOW_Y - SORD_HEIGHT);
	data->imgs.mini_map = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	mlx_image_to_window(data->mlx, data->imgs.mini_map, 0, 0);
	set_frames(data);
	raycast(data);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_player	player;

	if (ac != 2)
		put_error("Usage: ./cube <map_file>", NULL);
	data.player = &player;
	check_map_validity(av[1]);
	fill_the_data(&data, av[1]);
	set_data(&data);
	data.mlx = mlx_init(data.pxl_width, data.pxl_height, "cub3D", false);
	if (!data.mlx)
		put_error("mlx_init error", data.map);
	get_images(&data);
	mlx_loop_hook(data.mlx, move_player, (void *)&data);
	mlx_loop_hook(data.mlx, rotate, &data);
	mlx_loop_hook(data.mlx, door_func, &data);
	mlx_loop_hook(data.mlx, gun_func, &data);
	mlx_cursor_hook(data.mlx, cursor_func, &data);
	mlx_loop(data.mlx);
	free_resourses(&data);
	mlx_terminate(data.mlx);
}
