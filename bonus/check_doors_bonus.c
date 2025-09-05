/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidnassa <aidnassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:16:13 by aidnassa          #+#    #+#             */
/*   Updated: 2025/08/30 13:16:14 by aidnassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

void	check_map_doors(char **map)
{
	int	x;
	int	y;
	int	ok;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			ok = 0;
			if (map[y][x] == 'D')
			{
				if (map[y][x - 1] == '1' && map[y][x + 1] == '1')
					ok++;
				if (map[y - 1][x] == '1' && map[y + 1][x] == '1')
					ok++;
				if (ok != 1)
					put_error("door should surrounded by walls in one side",
						map);
			}
		}
	}
}
