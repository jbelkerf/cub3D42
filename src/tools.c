/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:12:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/08/27 20:31:17 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

mlx_texture_t	*safe_load_texture(char *path)
{
	mlx_texture_t	*tex;

	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = 0;
	tex = mlx_load_png(path);
	if (!tex)
	{
		printf(RED "failed to load texeture |%s|\n", path);
		exit(1);
	}
	return (tex);
}

double	get_start_angle(char **map, double p_x, double p_y)
{
	if (map[(int)(p_y / SCALE2D)][(int)(p_x / SCALE2D)] == 'N')
		return (3 * M_PI / 2);
	if (map[(int)(p_y / SCALE2D)][(int)(p_x / SCALE2D)] == 'S')
		return (M_PI / 2);
	if (map[(int)(p_y / SCALE2D)][(int)(p_x / SCALE2D)] == 'E')
		return (0);
	return (M_PI);
}

void	set_data(t_data *data)
{
	locate_player(data, data->map);
	data->map_width -= 1;
	data->pixel_width = WINDOW_X;
	data->pixel_height = WINDOW_Y;
	data->texts.north = safe_load_texture(data->north_texture);
	data->texts.east = safe_load_texture(data->east_texture);
	data->texts.south = safe_load_texture(data->south_texture);
	data->texts.west = safe_load_texture(data->west_texture);
	data->player->angle = get_start_angle(data->map, data->player->p_x, data->player->p_y);
}
