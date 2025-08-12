#include "../include/cube.h"

void	render_img(char **map, mlx_t *mlx, mlx_image_t *wall_img, char symbol)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (c == symbol || (symbol == '0' && (c == 'N' || c == 'C')))
				mlx_image_to_window(mlx, wall_img, x * SCALE2D, y * SCALE2D);
			x++;
		}
		y++;
	}
}

mlx_image_t	*create_render(mlx_t *mlx, char *img_file, int symbol, char **map)
{
	mlx_texture_t	*img_tex;
	mlx_image_t		*img;

	img_tex = mlx_load_png(img_file);
	// if (!img_tex)
	// 	free_map_and_error("texture can't be loaded", &map);
	img = mlx_texture_to_image(mlx, img_tex);
	mlx_delete_texture(img_tex);
	mlx_resize_image(img, SCALE2D, SCALE2D);
	render_img(map, mlx, img, symbol);
	return (img);
}