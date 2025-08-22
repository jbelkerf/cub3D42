/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:49:30 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/22 19:46:50 by JbelkerfIse      ###   ########.fr       */
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
				data->player->p_x = (j + 0.5) * SCALE2D;
				data->player->p_y = (i + 0.5) * SCALE2D;
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
	mlx_image_t	*img;

	data->imgs.background = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
	mlx_image_to_window(data->mlx, data->imgs.background, 0, 0);
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
	double dx = 0;
	double dy = 0;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if(mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
		dx = cos(data->player->angle);
		dy = sin(data->player->angle); 
		raycast(data);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
		dx = cos(data->player->angle + M_PI);
		dy = sin(data->player->angle + M_PI);
		raycast(data);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
		dx = cos(data->player->angle - (M_PI / 2));
		dy = sin(data->player->angle - (M_PI / 2));
		raycast(data);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
		dx = cos(data->player->angle + (M_PI / 2));
		dy = sin(data->player->angle + (M_PI / 2));
		raycast(data);
	}
	if ((dx != 0 || dy != 0) && data->map[(int)((data->player->p_y - 0.5 + dy)/ SCALE2D )][(int)((data->player->p_x - 0.5 + dx)/ SCALE2D) ] != '1')
	{
		//printf("dx dy: [%f %f] player [%f %f] instance [%d %d]\n", dx, dy, data->player->p_x, data->player->p_y, (data->imgs.player->instances[0].x - 10), (data->imgs.player->instances[0].y - 10));
		data->player->p_x += dx;
		data->player->p_y += dy;
		data->imgs.player->instances[0].y = (int)data->player->p_y - (SCALE2D / 2);
		data->imgs.player->instances[0].x = (int)data->player->p_x - (SCALE2D / 2);
		printf("player at: [%f %f]\n", data->player->p_x / SCALE2D, data->player->p_y/ SCALE2D);
	}
}


void rotate(mlx_key_data_t keydata, void *param)
{
	t_data *data;
	double rot_speed;
	
	data = param;
	rot_speed = 0.07;
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
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
