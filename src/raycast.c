#include "../include/cube.h"

// void render3d(double distance, int raw, unsigned col, t_data *data)
// {
// 	int	start;
// 	int	end;

// 	if (raw > WINDOW_X)
// 		return ;
// 	int wall_height = (WINDOW_Y / distance);
// 	start = (WINDOW_Y / 2) - (wall_height / 2);
// 	end = (WINDOW_Y / 2) + (wall_height / 2);
// 	if (start < 0)
// 		start = 0;
// 	if (end > WINDOW_Y)
// 		end = WINDOW_Y;
// 	while (start < end)
// 	{
// 		mlx_put_pixel(data->imgs.C3D, raw, start, col);
// 		start += 1;
// 	}
// }



uint32_t rgba_to_int(uint8_t *pixels)
{
	return ((uint32_t)(pixels[0] << 24) | (uint32_t)(pixels[1] << 16) | (uint32_t)(pixels[2] << 8) | (uint32_t)pixels[3]);
}

void render3d(double distance, int raw, mlx_texture_t *texture, t_data *data, int side, double ray_angle)
{
	int	start;
	int	end;

	if (raw > WINDOW_X )
		return ;
	int wall_height = (WINDOW_Y / distance);
	start = (WINDOW_Y / 2) - (wall_height / 2);
	end = (WINDOW_Y / 2) + (wall_height / 2);
	if (start < 0)
		start = 0;
	if (end > WINDOW_Y)
		end = WINDOW_Y;
	double	wallX;
	printf("ray: [%d] ray_angle: [%f]\n", raw, ray_angle * 180 / M_PI);
	if (!side)
		wallX = ((data->player->p_y - 0.5) / SCALE2D) + distance * sin(ray_angle);
	else
		wallX = ((data->player->p_x - 0.5) / SCALE2D) + distance * cos(ray_angle);
	wallX -= floor(wallX);

	int textX = (int)(wallX * (double)texture->width);
	if ((side == 0 && cos(ray_angle) < 0) || (side != 0 && sin(ray_angle ) > 0))
		textX = texture->width - textX - 1;
	textX = fmax(0, fmin(textX, texture->width - 1));
	int y = start;
	while (y < end)
	{
		if (y < MINI_HEIGHT && raw < MINI_WIDTH) //? do not overwrite the minimap
		{
			y++;
			continue;
		}
		int textY = (((y - start) * texture->height / wall_height) );
		uint8_t * pixel = &(texture->pixels[4 * (textY *texture->width + textX)]);
		mlx_put_pixel(data->imgs.C3D, raw, y, rgba_to_int(pixel));
		y++;
	}
}
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

void raycast(t_data *data)
{
    // ray(data);
    
	double dist;
	
    double player_x = (data->player->p_x - 0.5) / SCALE2D;
    double player_y = (data->player->p_y - 0.5) / SCALE2D;
    
	double angle = data->player->angle;
	
	int raw = 0;
	double ray_angle = angle - ((FOV * M_PI / 180) / 2);
	while (raw < WINDOW_X)
	{
		int cell_x = (int)player_x;
    	int cell_y = (int)player_y;
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
		//printf("angle: [%f] ray_angle: [%f] dist: [%f] ray: [%d]\n", angle, ray_angle, dist, raw);
		ray_angle += (FOV * M_PI / 180) / WINDOW_X;
		raw++;
	}
	render_mini_map(data);
}