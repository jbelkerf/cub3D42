/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:16:13 by aidnassa          #+#    #+#             */
/*   Updated: 2025/09/05 15:09:00 by JbelkerfIse      ###   ########.fr       */
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
