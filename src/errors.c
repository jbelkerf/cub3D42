/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:35:42 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/06 11:35:44 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	comma_count(char *line)
{
	int	c;

	c = 0;
	while (*line)
	{
		if (*line == ',')
			c++;
		line++;
	}
	return (c);
}

void	put_error(char *err, char **map)
{
	printf(RED "Error\n\t");
	printf(RED "%s\n" RESET, err);
	if (map)
		free_arr(map);
	exit(1);
}
