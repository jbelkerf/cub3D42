#include "../include/cube.h"

void ray(t_data *data, double start_x, double start_y)
{
	double ang = data->player->angle;
	double m = 0;
	double x = data->player->p_x - start_x;
	double y = (data->player->p_y) - start_y;
	double dx = cos(ang);
	double dy = sin(ang);
	while (m < WINDOW_X)
	{
		double xx;
		double yy;
		xx = x + (double)(dx  * m);
		yy = y + (double)(dy * m);
		if (xx >= 0 && xx + SCALE2D < MINI_WIDTH && yy >= 0 && yy + SCALE2D < MINI_HEIGHT)
		{
			if (data->map[(int)(yy + (SCALE2D / 2)) / SCALE2D][((int)(xx + (SCALE2D / 2)) / SCALE2D)] == '1')
				break ;
			mlx_put_pixel(data->imgs.mini_map, xx + SCALE2D, yy + SCALE2D, 0xff0000ff);
		}
		m+=1;	
	}
}

void	raycast(t_data *data)
{
	double	dist;
	double	player_x;
	double	player_y;
	double	angle;
	int		raw;
	double	ray_angle;
	int		cell_x;
	int		cell_y;

	player_x = (data->player->p_x - 0.5) / SCALE2D;
	player_y = (data->player->p_y - 0.5) / SCALE2D;
	angle = data->player->angle;
	raw = 0;
	ray_angle = angle - ((FOV * M_PI / 180) / 2);
	while (raw < WINDOW_X)
	{
		cell_x = (int)player_x;
		cell_y = (int)player_y;
		double ray_dx = cos(ray_angle);
		double ray_dy = sin(ray_angle);
		int step_x = 1;
		int step_y = 1;
		if (ray_dx < 0)
			step_x = -1;
		if (ray_dy < 0)
			step_y = -1;
		
		double delta_x = INFINITY;
		double delta_y = INFINITY;
		if (ray_dx != 0)
			delta_x = fabs(1.0 / ray_dx);
		if (ray_dy != 0)
			delta_y = fabs(1.0 / ray_dy);

		double side_x, side_y;
		
		if (ray_dx < 0)
			side_x = (player_x - cell_x) * delta_x;
		else
			side_x = (cell_x + 1.0 - player_x) * delta_x;
		if (ray_dy < 0)
			side_y = (player_y - cell_y) * delta_y;
		else
			side_y = (cell_y + 1.0 - player_y) * delta_y;
		
		int hit = 0;
		int side;
		
		while (hit == 0)
		{
			if (side_x < side_y)
			{
				side_x += delta_x;
				cell_x += step_x;
				side = 0;
			} else 
			{
				side_y += delta_y;
				cell_y += step_y;
				side = 1;
			}
			if (data->map[cell_y][cell_x] == '1')
				hit = 1;
		}

		if (side == 0)
			dist = (cell_x - player_x + (1 - step_x) / 2) / ray_dx;
		else
			dist = (cell_y - player_y + (1 - step_y) / 2) / ray_dy;
		mlx_texture_t *texture;

		if (side)
		{
			if (ray_dy > 0)
				texture = data->texts.north;
			else
				texture = data->texts.south;
		}
		else
		{
			if (ray_dx > 0)
				texture = data->texts.east;
			else
				texture = data->texts.west;
		}
		dist *= cos(angle - ray_angle);
		if (dist < 0)
			dist = 0;
		render3d(dist, raw, texture, data, side, ray_angle);
		ray_angle += (FOV * M_PI / 180) / WINDOW_X;
		raw++;
	}
	render_mini_map(data);
}