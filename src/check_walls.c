/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:41:24 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/09 16:26:56 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	check_map_walls(char **map, int length)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr2("0NEWS", map[y][x]))
			{
				if (y == 0 || y == length || x == 0 || x == ft_strlen(map[y]))
				{
					free_arr(map);
					put_error("map not soronded");
				}
				else if (!(ft_strchr2("0NEWS1", map[y][x + 1]) && ft_strchr2("0NEWS1", map[y][x - 1])
						&& ft_strchr2("0NEWS1", map[y + 1][x]) && ft_strchr2("0NEWS1", map[y - 1][x])))
				{
					free_arr(map);
					put_error("map not soronded2");
				}
			}
			x++;
		}
		y++;
	}
}
