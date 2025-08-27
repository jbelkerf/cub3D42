#include "../include/cube.h"

void move_player(void *param)
{
	t_data * data;
	double dx = 0;
	double dy = 0;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		free_resourses(data);
		mlx_close_window(data->mlx);
		// mlx_terminate(data->mlx);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
		dx = cos(data->player->angle);
		dy = sin(data->player->angle); 
		raycast(data);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
		dx = cos(data->player->angle + M_PI);
		dy = sin(data->player->angle + M_PI);
		raycast(data);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
		dx = cos(data->player->angle - (M_PI / 2));
		dy = sin(data->player->angle - (M_PI / 2));
		raycast(data);
	}
	if(mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
		dx = cos(data->player->angle + (M_PI / 2));
		dy = sin(data->player->angle + (M_PI / 2));
		raycast(data);
	}
	if ((dx != 0 || dy != 0) && data->map[(int)((data->player->p_y - 0.5 + dy)/ SCALE2D )][(int)((data->player->p_x - 0.5 + dx)/ SCALE2D) ] != '1')
	{
		//printf("dx dy: [%f %f] player [%f %f] instance [%d %d]\n", dx, dy, data->player->p_x, data->player->p_y, (data->imgs.player->instances[0].x - 10), (data->imgs.player->instances[0].y - 10));
		data->player->p_x += dx;
		data->player->p_y += dy;
		// data->imgs.player->instances[0].y = (int)data->player->p_y - (SCALE2D / 2);
		// data->imgs.player->instances[0].x = (int)data->player->p_x - (SCALE2D / 2);
		// printf("player at: [%f %f]\n", data->player->p_x / SCALE2D, data->player->p_y/ SCALE2D);
	}
}



void rotate(mlx_key_data_t keydata, void *param)
{
	t_data *data;
	double rot_speed;
	
	data = param;
	rot_speed = 0.07;
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
	{
		mlx_delete_image(data->mlx, data->imgs.C3D);
		data->imgs.C3D = mlx_new_image(data->mlx, data->pixel_width, data->pixel_height);
		mlx_image_to_window(data->mlx, data->imgs.C3D, 0, 0);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		data->player->angle += rot_speed;
		if (data->player->angle > 2 * M_PI)
			data->player->angle -= 2 * M_PI;
		raycast(data);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		data->player->angle -= rot_speed;
		if (data->player->angle < 0)
			data->player->angle += 2 * M_PI;
		raycast(data);
	}
}
