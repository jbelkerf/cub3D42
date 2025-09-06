/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 11:31:35 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/06 11:32:00 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

static void	check_doors_error(char **map, int ok, int door)
{
	if (door > MAX_DOORS)
		put_error("max doors exceeded", map);
	if (ok != 1)
		put_error("door should surrounded by walls in one side",
			map);
}

void	check_map_doors(char **map)
{
	int	x;
	int	y;
	int	ok;
	int	door;

	y = -1;
	door = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			ok = 0;
			if (map[y][x] == 'D')
			{
				door++;
				if (map[y][x - 1] == '1' && map[y][x + 1] == '1')
					ok++;
				if (map[y - 1][x] == '1' && map[y + 1][x] == '1')
					ok++;
				check_doors_error(map, ok, door);
			}
		}
	}
}
