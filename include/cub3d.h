/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:31:24 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/30 14:01:14 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "colors.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>

/*ERROR CODES*/
# define ERR_CUST		0
# define ERR_SYS		1
# define ERR_FD			2
# define ERR_TEXT		3
# define ERR_COLOR		4
# define ERR_MLX		5
# define ERR_ARGC		6
# define ERR_EXT		7

# define PI 3.14159265359
# define DR 0.0174533

typedef struct s_wall
{
	double	x;
	double	y;
	float	lineheight;
	int		thick;
	int		x_offset;
	int		y_offset;
}	t_wall;

typedef struct s_ray
{
	int		count;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	double	rx;
	double	ry;
	double	xo;
	double	yo;
	double	rangle;
	float	dis_h;
	float	hx;
	float	hy;
	float	dis_v;
	float	vx;
	float	vy;
	float	total_dis;
}	t_ray;

typedef struct s_player
{
	mlx_image_t		*img;
	int				start_x;
	int				start_y;
	double			x;
	double			y;
	double			pdx;
	double			pdy;
	double			pangle;
	double			pic_x;
	double			pic_y;
}	t_player;

typedef struct s_game_core
{
	mlx_t			*id;
	mlx_image_t		*img;
	t_player		*pj;
	int				xh_limit;
	int				yh_limit;
	int				xv_limit;
	int				yv_limit;
	int				last_time;
	int				current_time;
	int				delay;
	int				map[8][8];
}	t_game_core;

typedef struct s_paths
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_paths;

typedef struct s_data
{
	char			**map;
	t_player		*player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	int32_t			width;
	int32_t			height;
	uint32_t		sky;
	uint32_t		floor;
	mlx_texture_t	*n_wall;
	mlx_texture_t	*s_wall;
	mlx_texture_t	*e_wall;
	mlx_texture_t	*w_wall;
	t_paths			text_paths;
}	t_data;

/* -- main.c -- */
void	ft_draw_player(t_game_core *game, mlx_image_t *img);
void	ft_resize(int width, int height, void *param);

/* -- map.c -- */
int		get_rgba(int r, int g, int b, int a);
void	ft_draw_2d(void *param);
void	ft_map(t_game_core *game);
// void	ft_draw_pixels(void *param);

/* -- movement.c -- */
void	move_up(t_game_core *game);
void	move_down(t_game_core *game);
void	move_left(t_game_core *game);
void	move_right(t_game_core *game);

/* -- ft_init.c -- */

/**
 * @brief Initializes data structure and mlx related stuff
 * 
 * @param data 
 * @param file 
 */
void	ft_init(t_data *data, char *file);

/* -- ft_main_parser.c -- */

/**
 * @brief Function that handles all the parsing of the map
 * 
 * @param data 
 * @param file 
 */
void	ft_main_parser(t_data *data, char *file);

/* -- ft_map_check.c -- */

/**
 * @brief Checks map for invalid characters, player position and walls
 * 
 * @param data 
 */
void	ft_map_check(t_data *data);

/* -- ft_texture_check.c -- */

/**
 * @brief Checks if textures are correct
 * 
 * @param data 
 */
void    ft_texture_check(t_data *data);

/* -- ft_player_position.c -- */

/**
 * @brief Gets the position of the player and passes it to data struct
 * 
 * @param map 
 * @param data 
 */
void		ft_player_coords(t_data *data, char **map);

/* -- ft_exit.c -- */

/**
 * @brief Guess what this does, displays an error based on error code provided
 * 
 * @param data 
 * @param error 
 * @param msg 
 */
void	ft_errors(t_data *data, int error, char *msg);

/**
 * @brief Exits the whole program, who would have guessed
 * 
 * @param data 
 * @param status 
 */
void	ft_exit(t_data *data, int status);

/**
 * @brief Cleans arrays, duh
 * 
 * @param array 
 */
void	ft_clean_array(char **array);

/* -- ray_casting.c -- */
void	draw_rays(t_game_core *game);

/* -- ray_vertical_lines -- */
void	ft_vertical_lines(t_game_core *game, t_ray *ray);

/* -- ray_horizontal_lines -- */
void	ft_horizontal_lines(t_game_core *game, t_ray *ray);

/* -- Miscellaneus.c -- */
int		ft_get_time(void);
float	ft_distance(t_game_core *game, float end_x, float end_y);
void	ft_init_data_pj(t_game_core *data, t_player *pj, mlx_image_t *img);

/* -- Drawing.c -- */
void	ft_manage_3d_walls(t_game_core *game, t_ray *ray);
void	draw_pj(mlx_image_t *image, t_player *pj, int i);
void	draw_ray_line(mlx_image_t *image, t_player *pj, t_ray *ray, int i);

#endif