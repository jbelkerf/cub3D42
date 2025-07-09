/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:49:30 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/07/09 16:27:49 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./cube <map_file>\n", 2);
		return (1);
	}
	check_map_validity(av[1]);
	fill_the_data(&data, av[1]);
}
