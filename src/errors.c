/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:25:06 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/27 20:56:24 by JbelkerfIse      ###   ########.fr       */
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
