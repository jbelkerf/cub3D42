/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:06:43 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/07 18:07:24 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	match_texture(char *line, char *identifier, int file_fd)
{
	int		i;
	char	*err;

	err = NULL;
	if (ft_strncmp(line, identifier, ft_strlen(identifier)))
		err = "invalid identifier";
	i = ft_strlen(identifier);
	while (line[i] == ' ')
		i++;
	if (!err && i == ft_strlen(identifier))
		err = "invalid identifier";
	line[ft_strlen(line) - 1] = 0;
	i = open(line + i, O_RDONLY);
	free(line);
	if (err || i == -1)
	{
		if (!err && i == -1)
			err = "invalid texture";
		ft_putendl_fd(err, 2);
		close(file_fd);
		close(i);
		exit(1);
	}
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

int	is_valid_rgb(char *rgb)
{
	int	j;

	j = 0;
	if (ft_strlen(rgb) > 3)
		return (0);
	j = 0;
	while (rgb[j] && ft_isdigit(rgb[j]))
		j++;
	if (rgb[j] != '\0')
		return (0);
	if (ft_atoi(rgb) > 255)
		return (0);
	return (1);
}

void	match_rgb(char *identifier, int file_fd)
{
	char	*line;
	int		i;
	char	*err;
	char	**colors;

	err = NULL;
	line = skipi_abdsami3(file_fd);
	line[ft_strlen(line) - 1] = 0;
	if (!line)
		return ;
	if (!(line && line[0] == identifier[0] && line[1] == ' '))
		err = "invalid identifier";
	colors = ft_split(line + 2, ',');
	i = 0;
	while (colors[i] && i < 3)
	{
		if (!is_valid_rgb(colors[i++]))
			err = "invalid rgb";
	}
	if (i != 3 || colors[3])
		err = "invalid rgb";
	if (err)
	{
		free_arr(colors);
		free(line);
		close(file_fd);
		ft_putendl_fd(err, 2);
		exit(1);
	}
}

void	check_map_header(char *file)
{
	int		file_fd;

	file_fd = open(file, O_RDONLY);
	match_texture(skipi_abdsami3(file_fd), "NO", file_fd);
	match_texture(skipi_abdsami3(file_fd), "SO", file_fd);
	match_texture(skipi_abdsami3(file_fd), "WE", file_fd);
	match_texture(skipi_abdsami3(file_fd), "EA", file_fd);
	match_rgb("F", file_fd);
	match_rgb("C", file_fd);
}