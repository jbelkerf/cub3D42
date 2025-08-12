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

void raycast(t_data *data)
{
	int rays=0;
	mlx_delete_image(data->mlx, data->imgs.ray);
	data->imgs.ray = mlx_new_image(data->mlx, data->map_width * SCALE2D, data->map_length * SCALE2D);
	mlx_image_to_window(data->mlx, data->imgs.ray, 0 , 0);
	double ang = data->player->angle - (FOV / 2);
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
					render3d(fabs((ang - data->player->angle - (FOV / 2)) / var), xx, yy, data, col);
				}
				break ;
			}
			mlx_put_pixel(data->imgs.ray, xx, yy, 0xff0000ff);
			// ((udouble32_t *)data->imgs.ray->pixels)[yy * data->map_width *  SCALE2D + xx] = 0xff00ff00;
			m+=1;	
		}
		test++;
		rays++;
		ang += var;
	}
	// printf("test = %d\n", test);
}