/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:15:19 by jbelkerf          #+#    #+#             */
/*   Updated: 2025/08/28 13:30:12 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube_bonus.h"

uint32_t	rgba_to_int(uint8_t *pixels)
{
	return ((uint32_t)(pixels[0] << 24) | (uint32_t)(pixels[1] << 16) | (uint32_t)(pixels[2] << 8) | (uint32_t)pixels[3]);
}

void	render3d(double distance, int raw, mlx_texture_t *texture, t_data *data,
		int side, double ray_angle)
{
	int		start;
	int		end;
	int		old_start;
	int		textX;
	int		textY;
	int		wall_height;
	int		y;
	double	wallX;
	uint8_t	*pixel;

	if (raw > WINDOW_X)
		return ;
	wall_height = (WINDOW_Y / distance);
	start = (WINDOW_Y / 2) - (wall_height / 2);
	end = (WINDOW_Y / 2) + (wall_height / 2);
	old_start = 0;
	if (start < 0)
	{
		old_start = start;
		start = 0;
	}
	if (end > WINDOW_Y)
		end = WINDOW_Y;
	if (!side)
		wallX = ((data->player->p_y - 0.5) / SCALE2D) + (distance
				* sin(ray_angle));
	else
		wallX = ((data->player->p_x - 0.5) / SCALE2D) + (distance
				* cos(ray_angle));
	wallX -= floor(wallX);
	textX = (int)(wallX * (double)texture->width);
	if ((side == 0 && cos(ray_angle) < 0) || (side != 0 && sin(ray_angle) > 0))
		textX = texture->width - textX - 1;
	textX = fmax(0, fmin(textX, texture->width - 1));
	y = start;
	while (y < end)
	{
		if (y < MINI_HEIGHT && raw < MINI_WIDTH)
			//? do not overwrite the minimap
		{
			y++;
			continue ;
		}
		if (start)
			textY = (((y - start) * texture->height / wall_height));
		else
			textY = (((y - old_start) * texture->height / wall_height));
		if (!(textY < 0 || (uint32_t)textY >= texture->height || y >= WINDOW_Y))
		{
			pixel = &(texture->pixels[4 * (textY * texture->width + textX)]);
			mlx_put_pixel(data->imgs.CUB, raw, y, rgba_to_int(pixel));
		}
		y++;
	}
}
