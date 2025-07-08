/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:06:43 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/08 13:38:59 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	match_texture(char *line, char *identifier, int file_fd)
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
		put_error(err);
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

void	match_rgb(char *line)
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
		put_error(err);
	}
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
	int		file_fd;
	int		checker;
	char	*line;

	file_fd = open(file, O_RDONLY);
	checker = 0;
	while (checker != 63)
	{
		line = skipi_abdsami3(file_fd);
		if (line && !(checker & 1) && !ft_strncmp(line, "NO ", 3))
		{
			checker = checker | 1;
			match_texture(line, "NO ", file_fd);
		}
		else if (line && !(checker & 2) && !ft_strncmp(line, "SO ", 3))
		{
			checker = checker | 2;
			match_texture(line, "SO ", file_fd);
		}
		else if (line && !(checker & 4) && !ft_strncmp(line, "WE ", 3))
		{
			checker = checker | 4;
			match_texture(line, "WE ", file_fd);
		}
		else if (line && !(checker & 8) && !ft_strncmp(line, "EA ", 3))
		{
			checker = checker | 8;
			match_texture(line, "EA ", file_fd);
		}
		else if (line && !(checker & 16) && !ft_strncmp(line, "F ", 2))
		{
			checker = checker | 16;
			match_rgb(line);
		}
		else if (line && !(checker & 32) && !ft_strncmp(line, "C ", 2))
		{
			checker = checker | 32;
			match_rgb(line);
		}
		else
		{
			put_error("unexpected line");
		}
	}
}
