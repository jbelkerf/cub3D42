/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resourses_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:38:16 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/09/05 12:40:30 by jbelkerf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

char	**free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	free_resourses(t_data *data)
{
	free_arr(data->map);
	free(data->north_texture);
	free(data->south_texture);
	free(data->east_texture);
	free(data->west_texture);
	free(data->door_texture);
	free(data->texts.east);
	free(data->texts.west);
	free(data->texts.north);
	free(data->texts.south);
	free(data->texts.door);
	free(data->frames.aim);
	free(data->frames.fire);
}
