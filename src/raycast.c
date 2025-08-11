#include "../include/cube.h"


void raycast(t_data *data)
{
	int rays=0;
	mlx_delete_image(data->mlx, data->imgs.ray);
	data->imgs.ray = mlx_new_image(data->mlx, data->map_width * SCALE2D, data->map_length * SCALE2D);
	mlx_image_to_window(data->mlx, data->imgs.ray, 0 , 0);
	double ang = data->player->angle - (FOV / 2);
	while (ang <= data->player->angle + (FOV / 2))
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
				break ;
			mlx_put_pixel(data->imgs.ray, xx, yy, 0xff0000ff);
			// ((udouble32_t *)data->imgs.ray->pixels)[yy * data->map_width *  SCALE2D + xx] = 0xff00ff00;
			m+=1;	
		}
		rays++;
		ang += 1;
	}
}