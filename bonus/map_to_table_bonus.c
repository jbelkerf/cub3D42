/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_table_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:10:35 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/27 21:00:36 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

char	*resize_str(char *str, int new_size)
{
	char	*re;

	re = ft_calloc(new_size, sizeof(char));
	ft_strlcpy(re, str, ft_strlen(str) + 1);
	free(str);
	return (re);
}

int	start_the_map(char *line)
{
	if (!line)
		return (2);
	while (*line == ' ')
		line++;
	if (*line == '1' || *line == '0')
		return (1);
	return (0);
}

int	count_line(char *file, int *max_len)
{
	int		fd;
	int		line_count;
	char	*str;

	fd = open(file, O_RDONLY);
	line_count = 0;
	*max_len = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (start_the_map(str))
			break ;
		free(str);
	}
	while (str)
	{
		if (str && *max_len < ft_strlen(str))
			*max_len = ft_strlen(str);
		line_count++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	if (line_count == 0)
		put_error("Empty map", NULL);
	return (line_count);
}

char	**map_to_str(char *file, int *length, int *width)
{
	int		fd;
	char	*line;
	char	**re;
	int		i;

	*length = count_line(file, width);
	re = malloc((*length + 1) * sizeof(char *));
	fd = open(file, O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (start_the_map(line))
			break ;
		free(line);
	}
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		re[i++] = resize_str(line, *width + 1);
		line = get_next_line(fd);
	}
	return (re[i] = NULL, close(fd), re);
}
