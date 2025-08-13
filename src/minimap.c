#include "../include/cube.h"

void remove_the_player_bit(t_data *data)
{
	int x;
	int y = 0;

	while (y < data->map_length)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (ft_strchr("NEWS", data.map[y][x]))
			
			x++;
		}
		y++;
	}
}

void render_mini_map(data)
{
	remove_the_player_bit(data);
}
