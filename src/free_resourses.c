#include "../include/cube.h"

void	free_resourses(t_data *data)
{
	free_arr(data->map);
	free(data->north_texture);
	free(data->south_texture);
	free(data->east_texture);
	free(data->west_texture);
	free(data->texts.east);
	free(data->texts.west);
	free(data->texts.north);
	free(data->texts.south);
}
