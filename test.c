#include "include/cube.h"
uint32_t	rgba_to_int(uint8_t *pixels)
{
	return ((uint32_t)(pixels[0] << 24) | (uint32_t)(pixels[1] << 16)
	| (uint32_t)(pixels[2] << 8) | (uint32_t)pixels[3]);
}

int main()
{
    mlx_t *mlx;
    mlx_texture_t *txt;
    uint8_t *pixels;
    int tx, ty;

    txt = mlx_load_png("textures/sord.png");
    printf("width: %d, height: %d\n", txt->width, txt->height);
    mlx = mlx_init(800, 600, "My MLX Window", true);
    if (!mlx)
        return 1;
    mlx_image_t *img = mlx_new_image(mlx, 800, 600);
    ft_memset(img->pixels, 255, 800 * 600 * sizeof(int));
    int  x = 0;
    while (x < 800)
    {
        int y = 0;
        while (y < 600)
        {
            tx = (x * txt->width) / 800;
            ty = (y * txt->height) / 600;
            pixels = &txt->pixels[ 4 * (ty * txt->width + tx + tx)];
            if (rgba_to_int(pixels) != 0x00000000)
                mlx_put_pixel(img, x, y, rgba_to_int(pixels));
            else
                mlx_put_pixel(img, x, y, 0xFF0000FF);
            y++;
        }
        x++;
    }
    
    mlx_image_to_window(mlx, img, 0, 0);
    mlx_loop(mlx);
    return 0;
}