/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:48:37 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/28 15:40:30 by JbelkerfIse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../Libft/libft.h"
# include "../gnl/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include "../MLX42/include/MLX42/MLX42.h"
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define ORANGE  "\033[0;33m"
# define RESET   "\033[0m"


# define ROTATE_SPEED 0.07
# define FOV 60.0
# define SCALE2D 20
# define WINDOW_X 1500
# define WINDOW_Y 1000
# define MOVE_PIX 4
# define VISIBILTY 255
# define WALL_HEIGHT 700
# define WALL_UP_COLOR 0x800080ff
# define WALL_DOWN_COLOR 0x9932CCff
# define WALL_LEFT_COLOR 0x000000ff
# define WALL_RIGHT_COLOR 0xDA70D6ff


typedef struct s_imgs
{
	mlx_image_t	*ray;
	mlx_image_t	*background;
	mlx_image_t	*CUB;
}	t_imgs;


typedef struct s_player
{
	double	p_x;
	double	p_y;
	double	angle;
}	t_player;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*west;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
}	t_textures;

typedef struct s_data
{
	mlx_t		*mlx;
	char		**map;
	int			map_length;
	int			map_width;
	int			pxl_width;
	int			pxl_height;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_rgb[3];
	int			ceil_rgb[3];
	int			ceil_start;
	int			floor_start;
	double		dx;
	double		dy;
	t_player	*player;
	t_imgs		imgs;
	t_textures	texts;
}	t_data;
typedef struct s_raycast_md
{
	int				raw;
	int				side;
	int				cell_x;
	int				cell_y;
	int				step_x;
	int				step_y;
	double			side_x;
	double			side_y;
	double			ray_dx;
	double			ray_dy;
	double			player_x;
	double			player_y;
	double			delta_x;
	double			delta_y;
	double			dist;
	double			ray_angle;
	t_data			*data;
	mlx_texture_t	*texture;
}	t_raycast_md;

//CHECK MAP
void	check_map_validity(char *file);
void	check_map_header(char *file);
void	check_map_walls(char **map, int length);

// FILL the DATA
void	fill_the_data(t_data *data, char *file);

//TOOLS
char	**map_to_str(char *file, int *length, int *width);
char	*skipi_abdsami3(int file_fd);

//ERRORS
void	put_error(char *err, char **map);

// FREE RESOURCES
char	**free_arr(char **arr);

// Raycast
void	raycast(t_data *data);

// Rotate
void	rotate(void *param);

// render MiniMap
void	render_mini_map(t_data *data);
void	locate_player(t_data *data, char **map);
void	ray(t_data *data, double start_x, double start_y);

// Render3d
void	render3d(t_raycast_md *md);

//Move player
void	move_player(void *param);

//free resourses
void	free_resourses(t_data *data);

//tools
void	set_data(t_data *data);

#endif
