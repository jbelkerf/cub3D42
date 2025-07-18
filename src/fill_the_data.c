/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:17 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/10 15:22:08 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

char	*get_texture_path(char *file, char *identifier)
{
	int		fd;
	char	*path;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		put_error("opne error");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), NULL);
		if (!ft_strncmp(line, identifier, 3))
		{
			path = ft_strtrim(line + 2, " ");
			return (free(line), close(fd), path);
		}
		free(line);
	}
	return (close(fd), NULL);
}

void	set_rgb(char *file, char *identifier, int *rgb)
{
	int		fd;
	char	*line;
	char	**colors;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		put_error("opne error");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (close(fd), put_error("RGB not found"));
		if (!ft_strncmp(line, identifier, 2))
		{
			str = ft_strtrim(line + 2, " ");
			free(line);
			colors = ft_split(str, ',');
			free(str);
			rgb[0] = ft_atoi(colors[0]);
			rgb[1] = ft_atoi(colors[1]);
			rgb[2] = ft_atoi(colors[2]);
			return (free_arr(colors), close(fd), (void)31337);
		}
		free(line);
	}
	close(fd);
}

void	fill_the_data(t_data *data, char *file)
{
	data->east_texture = get_texture_path(file, "EA ");
	data->west_texture = get_texture_path(file, "WE ");
	data->north_texture = get_texture_path(file, "NO ");
	data->south_texture = get_texture_path(file, "SO ");
	set_rgb(file, "C ", data->ceil_rgb);
	set_rgb(file, "F ", data->floor_rgb);
	data->map = map_to_str(file, &(data->map_length), &(data->map_width));
}
