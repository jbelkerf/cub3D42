/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:06:43 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/27 16:09:27 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	m_t(char *line, char *identifier, int file_fd)
{
	int		i;
	char	*err;

	err = NULL;
	i = ft_strlen(identifier);
	while (line[i] == ' ')
		i++;
	line[ft_strlen(line) - 1] = 0;
	i = open(line + i, O_RDONLY);
	free(line);
	if (i == -1)
	{
		if (i == -1)
			err = "invalid texture";
		close(file_fd);
		close(i);
		put_error(err, NULL);
	}
	return (1);
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

int	match_rgb(char *line)
{
	int		i;
	char	*err;
	char	**colors;

	err = NULL;
	line[ft_strlen(line) - 1] = 0;
	i = 2;
	while (line[i] == ' ')
		i++;
	colors = ft_split(line + i, ',');
	free(line);
	i = 0;
	while (colors[i] && i < 3)
	{
		if (!is_valid_rgb(colors[i++]))
			err = "invalid rgb";
	}
	if (i != 3 || colors[3])
		err = "invalid rgb";
	free_arr(colors);
	if (err)
		put_error(err, NULL);
	return (1);
}

/*
	1 -> 0000 0001
	2 -> 0000 0010
	4 -> 0000 0100
	8 -> 0000 1000
	16-> 0001 0000
	32-> 0010 0000
*/

void	check_map_header(char *file)
{
	int		fd;
	int		chk;
	char	*ln;

	fd = open(file, O_RDONLY);
	chk = 0;
	while (chk != 63)
	{
		ln = skipi_abdsami3(fd);
		if (ln && !(chk & 1) && !ft_strncmp(ln, "NO ", 3) && m_t(ln, "NO ", fd))
			chk = chk | 1;
		else if (ln && !(chk & 2) && !ft_strncmp(ln, "SO ", 3) && m_t(ln, "SO ", fd))
			chk = chk | 2;
		else if (ln && !(chk & 4) && !ft_strncmp(ln, "WE ", 3) && m_t(ln, "WE ", fd))
			chk = chk | 4;
		else if (ln && !(chk & 8) && !ft_strncmp(ln, "EA ", 3) && m_t(ln, "EA ", fd))
			chk = chk | 8;
		else if (ln && !(chk & 16) && !ft_strncmp(ln, "F ", 2) && match_rgb(ln))
			chk = chk | 16;
		else if (ln && !(chk & 32) && !ft_strncmp(ln, "C ", 2) && match_rgb(ln))
			chk = chk | 32;
		else
			put_error("unexpected line", NULL);
	}
}
