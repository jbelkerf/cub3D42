/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:49:30 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/27 15:32:38 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

unsigned int	get_color(int *cols)
{
	return (cols[0] << 24 | cols[1] << 16 | cols[2] << 8 | VISIBILTY);
}

void	rnder_floor_and_ceil(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->pixel_height / 2)
	{
		x = 0;
		while (x < data->pixel_width)
		{
			mlx_put_pixel(data->imgs.background, x, y, get_color(data->ceil_rgb));
			x += 1;
		}
		y += 1;
	}
	y = data->pixel_height / 2;
	while (y < data->pixel_height)
	{
		x = 0;
		while (x < data->pixel_width)
		{
			mlx_put_pixel(data->imgs.background, x, y,  get_color(data->floor_rgb));
			x += 1;
		}
		y += 1;
	}
}

void	get_images(t_data *data)
{
	data->imgs.background = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
	mlx_image_to_window(data->mlx, data->imgs.background, 0, 0);
	data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
	mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
	rnder_floor_and_ceil(data);
	data->imgs.ray = mlx_new_image(data->mlx, MINI_WIDTH * SCALE2D, MINI_HEIGHT * SCALE2D);
	mlx_image_to_window(data->mlx, data->imgs.ray, 0 , 0);
	render_mini_map(data);
	raycast(data);
}


mlx_texture_t *safe_load_texture(char *path)
{
	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = 0;
	mlx_texture_t *tex = mlx_load_png(path);
	if (!tex)
	{
		printf(RED "failed to load texeture |%s|\n", path);
		exit(1);
	}
	return (tex);
}

void set_data(t_data *data)
{
	locate_player(data, data->map);
	data->map_width -= 1;
	data->pixel_width = WINDOW_X;
	data->pixel_height = WINDOW_Y;
	data->texts.north = safe_load_texture(data->north_texture);
	data->texts.east = safe_load_texture(data->east_texture);
	data->texts.south = safe_load_texture(data->south_texture);
	data->texts.west = safe_load_texture(data->west_texture);
	data->imgs.mini_map = NULL;
}

int	main(int ac, char **av)
{
	t_data		data;
	t_player	player;

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
	free_resourses(&data);
	mlx_terminate(data.mlx);
}
