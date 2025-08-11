#include "../include/cube.h"


void render3d(int raw, double x, double y, t_data *data)
{
	double	distance;
	double	p_x;
	double	p_y;
	int	start;
	int	end;
	if (raw > 1000)
		return ;
	p_x = data->imgs.player->instances[0].x;
	p_y = data->imgs.player->instances[0].y;
	distance = sqrt((p_x - x) * (p_x - x) + (p_y - y) * (p_y - y));
	end = WINDOW_Y - distance;
	start = WINDOW_Y - distance - WALL_HEIGHT;
	printf("start = %d end %d raw %d\n", start, end, raw);
	while (start < end)
	{
		mlx_put_pixel(data->imgs.C3D, start, raw, 0xffffffff);
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
	double var = FOV / 1000;
	while (var <= data->player->angle + (FOV / 2))
	{
		double m = 0;
		double x = data->imgs.player->instances[0].x + (SCALE2D / 2);
		double y = data->imgs.player->instances[0].y + (SCALE2D / 2);
		double dx = cos(ang * M_PI / 180.0);
		double dy = sin(ang * M_PI / 180.0);
		while (m < 1000)
		{
			double xx;
			double yy;
			xx = x + (double)(dx  * m);
			yy = y + (double)(dy * m);
			if (data->map[(int)(yy / SCALE2D)][(int)(xx / SCALE2D)] == '1' || !(xx <( data->map_width * SCALE2D ) && yy < (data->map_length * SCALE2D)  && xx > 0 && yy > 0))
			{
				if (data->map[(int)(yy / SCALE2D)][(int)(xx / SCALE2D)] == '1')
					render3d(fabs((ang - data->player->angle - (FOV / 2)) / var), xx, yy, data);
				break ;
			}
			mlx_put_pixel(data->imgs.ray, xx, yy, 0xff0000ff);
			// ((udouble32_t *)data->imgs.ray->pixels)[yy * data->map_width *  SCALE2D + xx] = 0xff00ff00;
			m+=1;	
		}
		rays++;
		ang += var;
	}
}