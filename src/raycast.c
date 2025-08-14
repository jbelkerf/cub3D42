#include "../include/cube.h"


void render3d(int raw, double x, double y, t_data *data, unsigned col)
{
	double	distance;
	double	p_x;
	double	p_y;
	int	start;
	int	end;
	if (raw > WINDOW_X)
		return ;
	p_x = data->imgs.player->instances[0].x;
	p_y = data->imgs.player->instances[0].y;
	distance = sqrt((p_x - x) * (p_x - x) + (p_y - y) * (p_y - y));
	if (distance == 0)
		return ;
	int wall_height = (WINDOW_Y / distance) * 10;
	start = (WINDOW_Y / 2) - (wall_height / 2);
	end = (WINDOW_Y / 2) + (wall_height / 2);
	if (start < 0)
		start = 0;
	if (end > WINDOW_Y)
		end = WINDOW_Y;
	while (start < end)
	{
		mlx_put_pixel(data->imgs.C3D, raw, start, col);
		start += 1;
	}
}
void ray(t_data *data)
{
	int rays=0;
	mlx_delete_image(data->mlx, data->imgs.ray);
	data->imgs.ray = mlx_new_image(data->mlx, data->map_width * SCALE2D, data->map_length * SCALE2D);
	mlx_image_to_window(data->mlx, data->imgs.ray, 0 , 0);
	double ang = data->player->angle;
	double var = FOV / WINDOW_X;
	int test = 0;
	while ((ang <= data->player->angle + (FOV / 2)) && test < WINDOW_X)
	{
		double m = 0;
		double x = data->imgs.player->instances[0].x + (SCALE2D / 2);
		double y = data->imgs.player->instances[0].y + (SCALE2D / 2);
		double dx = cos(ang * M_PI / 180.0);
		double dy = sin(ang * M_PI / 180.0);
		while (m < WINDOW_X)
		{
			double xx;
			double yy;
			xx = x + (double)(dx  * m);
			yy = y + (double)(dy * m);
			if (data->map[(int)(yy / SCALE2D)][(int)(xx / SCALE2D)] == '1' || !(xx <( data->map_width * SCALE2D ) && yy < (data->map_length * SCALE2D)  && xx > 0 && yy > 0))
			{
				if (data->map[(int)(yy / SCALE2D)][(int)(xx / SCALE2D)] == '1')
				{
					unsigned	col;
					if (fabs(xx - (int)(xx / SCALE2D) * SCALE2D) < fabs(yy - (int)(yy / SCALE2D) * SCALE2D))
					{
						// Vertical wall
						if (dx > 0)
							col = WALL_RIGHT_COLOR;
						else
							col = WALL_LEFT_COLOR;
					} else
					{
						// Horizontal wall
						if (dy > 0)
							col = WALL_DOWN_COLOR;
						else
							col = WALL_UP_COLOR;
					}
					//render3d(fabs((ang - data->player->angle - (FOV / 2)) / var), xx, yy, data, col);
				}
				break ;
			}
			mlx_put_pixel(data->imgs.ray, xx, yy, 0xff0000ff);
			// ((udouble32_t *)data->imgs.ray->pixels)[yy * data->map_width *  SCALE2D + xx] = 0xff00ff00;
			m+=1;	
		}
		break;
		test++;
		rays++;
		ang += var;
	}
	// printf("test = %d\n", test);
}
void raycast(t_data *data)
{
	// ray(data);
	double dist_x = 0;
	double dist_y = 0;
	double player_x = data->player->p_x / SCALE2D;
	double player_y = data->player->p_y / SCALE2D;

	int grid_x = (int)player_x;
	int grid_y = (int)player_y;

	printf("GRID: [%d %d]\n", grid_x, grid_y);
	double angle = data->player->angle;
	double sin_z = sin(angle * M_PI / 180);
	double cos_z = cos(angle * M_PI / 180);

	double step_x = fabs(1 / cos_z);
	double step_y = fabs(1 / sin_z);

	if (cos_z < 0)
		dist_x = (grid_x + 1 - (player_x)) * cos_z;
	else if (cos_z > 0)
		dist_x = (player_x - grid_x) * cos_z;
	else
		dist_x = INFINITY;
	
	if (sin_z > 0)
		dist_y = (player_y - grid_y) * sin_z;
	else if (sin_z < 0)
		dist_y = ((grid_y +  1) - player_y) * sin_z;
	else
		dist_y = INFINITY;

	while (data->map[grid_y][grid_x] != '1')
	{
		printf("grid x: %d, dist x: %f.\n\n", grid_x, dist_x);
		if (dist_x < dist_y)
		{
			if (cos_z > 0)
				grid_x++;
			else if (cos_z < 0)
				grid_x--;
			
			dist_x += step_x;
		}
		else
		{
			if (sin_z < 0)
				grid_y--;
			else if (sin_z > 0)
				grid_y++;
			dist_y += step_y;
		}
	}
	printf("dist [%f %f]\n", dist_x, dist_y);
	//printf("player at [%f %f] at angle %f\n", player_x / SCALE2D, player_y / SCALE2D, angle);
	
}