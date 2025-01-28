/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:35:55 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/28 15:06:15 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>

# define PI 3.14159265359
# define DR 0.0174533

typedef struct s_wall
{
	double	x;
	double	y;
	float	lineheight;
	int		thick;
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