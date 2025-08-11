/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:49:30 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/11 15:11:28 by JbelkerfIse      ###   ########.fr       */
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
				data->player->p_x = j * SCALE;
				data->player->p_y = i * SCALE;
				break ;
			}
			j++;
		}
		i++;
	}
	data->player->angle = 0;
}

// void print_data(t_data *data)
// {
// 	int i;

// 	printf("Map Length: %d\n", data->map_length);
// 	printf("Map Width: %d\n", data->map_width);
// 	printf("North Texture: %s\n", data->north_texture);
// 	printf("South Texture: %s\n", data->south_texture);
// 	printf("West Texture: %s\n", data->west_texture);
// 	printf("East Texture: %s\n", data->east_texture);
// 	printf("Floor RGB: [%d, %d, %d]\n", data->floor_rgb[0], data->floor_rgb[1], data->floor_rgb[2]);
// 	printf("Ceiling RGB: [%d, %d, %d]\n", data->ceil_rgb[0], data->ceil_rgb[1], data->ceil_rgb[2]);
// 	for (i = 0; i < data->map_length; i++)
// 		printf("%s\n", data->map[i]);
// }

void	get_images(t_data *data)
{
	mlx_image_t	*img;

	img = create_render(data->mlx, floor_texture, '0', data->map);
	data->imgs.floor = img;
	img = create_render(data->mlx, wall_texture, '1', data->map);
	data->imgs.wall = img;
	img = create_render(data->mlx, player_texture, 'N', data->map);
	data->imgs.player = img;
	data->imgs.ray = mlx_new_image(data->mlx, data->map_width * SCALE, data->map_length * SCALE);
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
		data->imgs.player->instances[0].y += 5 * dy;
		data->imgs.player->instances[0].x += 5 * dx;
		// data->player->p_y -= MOVE_PIX;
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

void raycast(t_data *data)
{
	int rays=0;
	mlx_delete_image(data->mlx, data->imgs.ray);
	data->imgs.ray = mlx_new_image(data->mlx, data->map_width * SCALE, data->map_length * SCALE);
	mlx_image_to_window(data->mlx, data->imgs.ray, 0 , 0);
	double ang = data->player->angle - (FOV / 2);
	while (ang <= data->player->angle + (FOV / 2))
	{
		double m = 0;
		double x = data->imgs.player->instances[0].x + (SCALE / 2);
		double y = data->imgs.player->instances[0].y + (SCALE / 2);
		double dx = cos(ang * M_PI / 180.0);
		double dy = sin(ang * M_PI / 180.0);
		while (m < 1000)
		{
			double xx;
			double yy;
			xx = x + (double)(dx  * m);
			yy = y + (double)(dy * m);
			if (data->map[(int)(yy / SCALE)][(int)(xx / SCALE)] == '1' || !(xx <( data->map_width * SCALE ) && yy < (data->map_length * SCALE)  && xx > 0 && yy > 0))
				break ;
			mlx_put_pixel(data->imgs.ray, xx, yy, 0xff0000ff);
			// ((udouble32_t *)data->imgs.ray->pixels)[yy * data->map_width *  SCALE + xx] = 0xff00ff00;
			m+=1;	
		}
		rays++;
		ang += 1;
	}
	printf("rays %d\n",rays);
}

void rotate(mlx_key_data_t keydata, void *param)
{
	t_data *data;
	
	data = param;
	if (keydata.key == MLX_KEY_RIGHT)
	{
		printf("right\n");
		data->player->angle = fmod(data->player->angle + ROTATE_DEG, 360.0);
		raycast(data);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		printf("lft\n");
		data->player->angle = fmod(data->player->angle - ROTATE_DEG + 360.0, 360.0);
		raycast(data);
	}
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
	locate_player(&data, (data.map));
	// print_data(&data);  //!debuging purposes
	data.map_width = data.map_width -1 ;
	data.mlx = mlx_init(data.map_width * SCALE, data.map_length * SCALE, "cub3D", false);
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
