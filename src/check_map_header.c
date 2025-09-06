/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:35:15 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/06 11:35:16 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	poweroftwo(int exp)
{
	int	result;
	int	i;

	i = 0;
	result = 1;
	if (exp == 0)
		return (1);
	while (i < exp)
	{
		result *= 2;
		i++;
	}
	return (result);
}

int	match_texture(char *line, char *identifier, int file_fd, int *chk)
{
	int		i;
	char	*err;
	char	*shift;

	shift = "NSWE";
	err = NULL;
	i = ft_strlen(identifier);
	while (line[i] == ' ')
		i++;
	line[ft_strlen(line) - 1] = 0;
	i = open(line + i, O_RDONLY);
	if (i == -1
		|| !check_the_file_extention(line + ft_strlen(identifier) + 1, ".png"))
	{
		if (i == -1)
			err = "invalid texture";
		else
			err = "invalid texture extention";
		close(file_fd);
		close(i);
		return (free(line), put_error(err, NULL), 0);
	}
	free(line);
	*chk |= poweroftwo(ft_strchr(shift, identifier[0]) - shift);
	return (1);
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
	if (comma_count(line) != 2)
		err = "too much comma in rgb";
	colors = ft_split(line + i, ',');
	free(line);
	i = 0;
	while (colors[i] && i < 3 && !err)
	{
		if (!is_valid_rgb(colors[i++]))
			err = "invalid rgb";
	}
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
		if (ln && !(chk & 1) && !ft_strncmp(ln, "NO ", 3))
			match_texture(ln, "NO ", fd, &chk);
		else if (ln && !(chk & 2) && !ft_strncmp(ln, "SO ", 3))
			match_texture(ln, "SO ", fd, &chk);
		else if (ln && !(chk & 4) && !ft_strncmp(ln, "WE ", 3))
			match_texture(ln, "WE ", fd, &chk);
		else if (ln && !(chk & 8) && !ft_strncmp(ln, "EA ", 3))
			match_texture(ln, "EA ", fd, &chk);
		else if (ln && !(chk & 16) && !ft_strncmp(ln, "F ", 2) && match_rgb(ln))
			chk = chk | 16;
		else if (ln && !(chk & 32) && !ft_strncmp(ln, "C ", 2) && match_rgb(ln))
			chk = chk | 32;
		else
			put_error("unexpected line", NULL);
	}
}
