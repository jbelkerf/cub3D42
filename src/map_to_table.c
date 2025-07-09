/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:10:35 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/08 15:30:05 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

char	*resize_str(char *str, int new_size)
{
	char	*re;

	re = ft_calloc(new_size, sizeof(char));
	ft_strlcpy(re, str, ft_strlen(str));
	free(str);
	return (re);
}

int	count_line(char *file, int *max_len)
{
	int		fd;
	int		line_count;
	char	*str;

	fd = open(file, O_RDONLY);
	line_count = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (str[0] == 'C' && str[1] == ' ')
		{
			free(str);
			break ;
		}
		free(str);
	}
	str = skipi_abdsami3(fd);
	if (str)
	{
		*max_len = ft_strlen(str);
		line_count++;
		free(str);
	}
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		if (*max_len < ft_strlen(str))
			*max_len = ft_strlen(str);
		line_count++;
		free(str);
	}
	close(fd);
	if (line_count == 0)
	{
		ft_putendl_fd("emptys shit", 2);
		exit(1);
	}
	return (line_count);
}

char	**map_to_str(char *file)
{
	int		fd;
	char	*line;
	char	**re;
	int		i;
	int		max_len;

	re = malloc((count_line(file, &max_len) + 1) * sizeof(char *));
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line[0] == 'C' && line[1] == ' ')
		{
			free(line);
			break ;
		}
		free(line);
	}
	line = skipi_abdsami3(fd);
	i = 0;
	while (1)
	{
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		re[i] = resize_str(line, max_len);
		i++;
		line = get_next_line(fd);
	}
	re[i] = NULL;
	close(fd);
	return (re);
}
