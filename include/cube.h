/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JbelkerfIsel-mou <minishell>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:48:37 by JbelkerfIse       #+#    #+#             */
/*   Updated: 2025/08/05 20:41:38 by JbelkerfIse      ###   ########.fr       */
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
#include "../MLX42/include/MLX42/MLX42.h"

# define player_texture "textures/p.png" //!to be removed
# define floor_texture "textures/0.png" //!to be removed
# define wall_texture "textures/1.png" //!to  be removed
# define ROTATE_DEG 5
# define FOV 70.0
# define SCALE 50
# define MOVE_PIX 4

typedef struct s_imgs
{
	mlx_image_t	*player;
	mlx_image_t	*floor;
	mlx_image_t	*wall;
	mlx_image_t *ray;
}	t_imgs;

typedef struct s_player
{
	double	p_x;
	double	p_y;
	double	angle;
}	t_player;
typedef struct s_data
{
	mlx_t	*mlx;
	char	**map;
	int		map_length;
	int		map_width;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_rgb[3];
	int		ceil_rgb[3];
	t_player *player;
	t_imgs	imgs;
}	t_data;

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
void	put_error(char *err);

// FREE RESOURCES
char	**free_arr(char **arr);

// Raycast
void raycast(t_data *data);

// Rotate
void rotate(mlx_key_data_t keydata, void *param);

#endif
