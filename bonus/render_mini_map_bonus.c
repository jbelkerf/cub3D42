/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:39:22 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/08/27 22:41:34 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

mlx_image_t	*create_img(mlx_t *mlx, char *img_file)
{
	mlx_texture_t	*img_tex;
	mlx_image_t		*img;

	img_tex = mlx_load_png(img_file);
	img = mlx_texture_to_image(mlx, img_tex);
	mlx_delete_texture(img_tex);
	mlx_resize_image(img, SCALE2D, SCALE2D);
	return (img);
}

void	print_on_map(mlx_image_t *img, double center_x, double center_y, uint32_t color, int scale)
{
	int	x;
	int	y;

	x = (center_x * SCALE2D - (SCALE2D / scale));
	y = (center_y * SCALE2D - (SCALE2D / scale));
	while (y < (center_y * SCALE2D + (SCALE2D / scale)) && y < MINI_HEIGHT)
	{
		x = (center_x * SCALE2D - (SCALE2D / scale));
		while (x < (center_x * SCALE2D + (SCALE2D / scale)) && x < MINI_WIDTH)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_mini_map(t_data *data)
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;
	int	x;
	int	y;

	if (!data->imgs.mini_map)
	{
		data->imgs.mini_map = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
		mlx_image_to_window(data->mlx, data->imgs.mini_map, 0, 0);
	}
	y_start = (data->player->p_y / SCALE2D) - (MINI_HEIGHT / SCALE2D / 2);
	if (y_start < 0)
		y_start = 0;
	y_end = (MINI_HEIGHT / SCALE2D) + y_start;
	if (y_end > data->map_length)
		y_end = data->map_length;
	x_start = (data->player->p_x / SCALE2D)- (MINI_WIDTH / SCALE2D / 2);
	if (x_start < 0)
		x_start = 0;
	x_end = (MINI_HEIGHT / SCALE2D) + x_start;
	if (x_end > data->map_width)
		x_end = data->map_width;
	y = y_start;

	while (y < y_end)
	{
		x = x_start;
		while (x < x_end)
		{
			if (data->map[y][x] == '1')
				print_on_map(data->imgs.mini_map, x - x_start + 1, y - y_start + 1, 0x00ff00ff, 2);
			else if (ft_strchr("NWES0", data->map[y][x]))
				print_on_map(data->imgs.mini_map, x - x_start + 1, y - y_start + 1, 0x0000ffff, 2);
			x++;
		}
		y++;
	}
	print_on_map(data->imgs.mini_map, (data->player->p_x + (SCALE2D / 2)) / SCALE2D - x_start , (data->player->p_y + (SCALE2D / 2)) / SCALE2D - y_start , 0xff0000ff, 8);
	ray(data, (x_start  + 0.5) * SCALE2D, (y_start + 0.5) * SCALE2D);	
}
