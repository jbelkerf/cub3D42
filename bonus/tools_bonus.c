/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:12:33 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/05 13:36:05 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

mlx_texture_t	*safe_load_texture(char *path)
{
	mlx_texture_t	*png_tex;

	png_tex = NULL;
	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = 0;
	if (check_the_file_extention(path, ".png"))
		png_tex = mlx_load_png(path);
	else
	{
		printf(RED "invalid texture extention |%s|\n", path);
		exit(1);
	}
	if (!png_tex)
	{
		printf(RED "failed to load texeture |%s|\n", path);
		exit(1);
	}
	return (png_tex);
}

char	*skipi_abdsami3(int file_fd)
{
	char	*line;

	line = get_next_line(file_fd);
	if (!line)
		return (NULL);
	if (line[0] == '\n' && !line[1])
		return (free(line), skipi_abdsami3(file_fd));
	else
		return (line);
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
	double	tmp;

	locate_player(data, data->map);
	data->map_width -= 1;
	data->pxl_width = WINDOW_X;
	data->pxl_height = WINDOW_Y;
	data->texts.north = safe_load_texture(data->north_texture);
	data->texts.east = safe_load_texture(data->east_texture);
	data->texts.south = safe_load_texture(data->south_texture);
	data->texts.west = safe_load_texture(data->west_texture);
	data->texts.door = safe_load_texture(data->door_texture);
	tmp = get_start_angle(data->map, data->player->p_x, data->player->p_y);
	data->player->angle = tmp;
	data->door_idx = -1;
	data->front_door = -1;
	data->last_open_door = -1;
	data->mouse_last_x = -1;
	data->mouse_ignore_next = 0;
	ft_memset((void *)&data->doors_info, 0, sizeof(t_door_info *));
	data->imgs.mini_map = NULL;
}

int	check_the_file_extention(char *file, char *extention)
{
	int	x_len;
	int	f_len;

	x_len = ft_strlen(extention);
	f_len = ft_strlen(file);
	if (x_len >= f_len)
		return (0);
	while (--x_len >= 0)
	{
		if (file[--f_len] != extention[x_len])
			return (0);
	}
	if (file[f_len - 1] == '/')
		return (0);
	return (1);
}

void	set_frames(t_data *data)
{
	data->frames.aim_count = 0;
	data->frames.max_aim = 10;
	data->frames.max_fire = 7;
	data->frames.fire_count = 0;
	data->frames.frame_delay = FRAME_DELAY;
	data->frames.type = 2;
	data->frames.last_time = mlx_get_time();
	data->frames.aim = malloc(12 * sizeof(mlx_texture_t *));
	data->frames.fire = malloc(8 * sizeof(char *));
	data->frames.aim[0] = safe_load_texture("./textures/AIM/hk53_aim.1.png");
	data->frames.aim[1] = safe_load_texture("./textures/AIM/hk53_aim.2.png");
	data->frames.aim[2] = safe_load_texture("./textures/AIM/hk53_aim.3.png");
	data->frames.aim[3] = safe_load_texture("./textures/AIM/hk53_aim.4.png");
	data->frames.aim[4] = safe_load_texture("./textures/AIM/hk53_aimfire.1.png");
	data->frames.aim[5] = safe_load_texture("./textures/AIM/hk53_aimfire.2.png");
	data->frames.aim[6] = safe_load_texture("./textures/AIM/hk53_aimfire.3.png");
	data->frames.aim[7] = safe_load_texture("./textures/AIM/hk53_aimfire.4.png");
	data->frames.aim[8] = safe_load_texture("./textures/AIM/hk53_aimfire.5.png");
	data->frames.aim[9] = safe_load_texture("./textures/AIM/hk53_aimfire.6.png");
	data->frames.fire[0] = safe_load_texture("./textures/FIRE/hk53_fire.1.png");
	data->frames.fire[1] = safe_load_texture("./textures/FIRE/hk53_fire.2.png");
	data->frames.fire[2] = safe_load_texture("./textures/FIRE/hk53_fire.3.png");
	data->frames.fire[3] = safe_load_texture("./textures/FIRE/hk53_fire.4.png");
	data->frames.fire[4] = safe_load_texture("./textures/FIRE/hk53_fire.5.png");
	data->frames.fire[5] = safe_load_texture("./textures/FIRE/hk53_fire.6.png");
	data->frames.fire[6] = safe_load_texture("./textures/nw/hk53_idle.1.png");
}
