/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:12:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/08/27 21:31:23 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

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

// char	*skipi_abdsami3(int file_fd)
// {
// 	char	*line;

// 	line = get_next_line(file_fd);
// 	if (!line)
// 		return (NULL);
// 	if (line[0] == '\n' && !line[1])
// 		return (free(line), skipi_abdsami3(file_fd));
// 	else
// 		return (line);
// }

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
	double	tmp;

	locate_player(data, data->map);
	data->map_width -= 1;
	data->pxl_width = WINDOW_X;
	data->pxl_height = WINDOW_Y;
	data->texts.north = safe_load_texture(data->north_texture);
	data->texts.east = safe_load_texture(data->east_texture);
	data->texts.south = safe_load_texture(data->south_texture);
	data->texts.west = safe_load_texture(data->west_texture);
	tmp = get_start_angle(data->map, data->player->p_x, data->player->p_y);
	data->player->angle = tmp;
}
