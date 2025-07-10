/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:49:30 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/10 18:31:26 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		put_error("Usage: ./cube <map_file>");
	check_map_validity(av[1]);
	fill_the_data(&data, av[1]);
	// print_data(&data);  //!debuging perposes
	data.mlx = mlx_init(1000, 1000, "cub3D", 1);
	if (!data.mlx)
	{
		free_arr(data.map);
		put_error("mlx_init error");
	}
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}
