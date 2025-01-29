/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:04:50 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/29 15:51:43 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_wall_thickness(mlx_image_t *image, t_wall *wall)
{
	int	i;

	i = -1;
	while (++i < wall->thick)
		mlx_put_pixel(image, wall->x + wall->screen_offset + i, wall->y, get_rgba(51, 255, 54, 255));
}

static void	draw_wall_lines(mlx_image_t *image, t_ray *ray, t_wall *wall, int i)
{
	float	dx;
	float	dy;
	float	steps;
	float	increment_x;
	float	increment_y;

	wall->x = ray->rx;
	wall->y = ray->ry;
	dx = fabs(ray->rx - wall->x);
	dy = fabs((ray->ry - wall->lineheight) - wall->y);
	steps = fmax(dx, dy);
	increment_x = dx / steps; //increments each axis to know which points to draw
	increment_y = dy / steps;
	while (++i < steps && wall->y < 512 && wall->y > 0 && wall->x + wall->screen_offset < 1024 && wall->x + wall->screen_offset > 512) //to draw the points between the start (p1) and end (p2) point
	{
		wall->thick = 4;
		ft_wall_thickness(image, wall);
		if (ray->rx < wall->x)
			wall->x -= increment_x;
		else
			wall->x += increment_x;
		if (ray->ry - wall->lineheight < wall->y)
			wall->y -= increment_y;
		else
			wall->y += increment_y;
	}
}

void	ft_manage_3d_walls(t_game_core *game, t_ray *ray)
{
	t_wall	*wall;

	wall = malloc(sizeof(t_wall));
	if (!wall)
		exit(EXIT_FAILURE);
	wall->lineheight = (64 * 320) / ray->total_dis; //cube size * wall desired height. Distance to wall changes size
	if (wall->lineheight > 320)
		wall->lineheight = 320;
	wall->screen_offset = (ray->rx - 512) * -1 + (ray->count * 4);//(ray->count * 8 + 530) / 2;
	draw_wall_lines(game->img, ray, wall, -1);
}

static void	ft_draw_pj_icon(mlx_image_t *image, t_player *pj)
{
	mlx_put_pixel(image, pj->pic_x, pj->pic_y, get_rgba(51, 255, 246, 255));
	mlx_put_pixel(image, pj->pic_x, pj->pic_y + 1, get_rgba(51, 255, 246, 255));
	mlx_put_pixel(image, pj->pic_x + 1, pj->pic_y, get_rgba(51, 255, 246, 255));
	mlx_put_pixel(image, pj->pic_x, pj->pic_y - 1, get_rgba(51, 255, 246, 255));
	mlx_put_pixel(image, pj->pic_x - 1, pj->pic_y, get_rgba(51, 255, 246, 255));
}

void	draw_pj(mlx_image_t *image, t_player *pj, int i)
{
	double	dx;
	double	dy;
	double	steps;
	double	increment_x;
	double	increment_y;

	pj->pic_x = pj->x;
	pj->pic_y = pj->y;
	dx = fabs(pj->pdx * 5);
	dy = fabs(pj->pdy * 5);
	steps = fmax(dx, dy);
	increment_x = dx / steps; //increments each axis to know which points to draw
	increment_y = dy / steps;
	while (++i < steps) //to draw the points between the start (p1) and end (p2) point
	{
		ft_draw_pj_icon(image, pj);
		if (pj->pdx + pj->x < pj->x)
			pj->pic_x -= increment_x;
		else
			pj->pic_x += increment_x;
		if (pj->pdy + pj->y < pj->y)
			pj->pic_y -= increment_y;
		else
			pj->pic_y += increment_y;
	}
}

void	draw_ray_line(mlx_image_t *image, t_player *pj, t_ray *ray, int i)
{
	float	dx;
	float	dy;
	float	steps;
	float	increment_x;
	float	increment_y;

	pj->pic_x = pj->x;
	pj->pic_y = pj->y;
	dx = fabs(ray->rx - pj->pic_x);
	dy = fabs(ray->ry - pj->pic_y);
	steps = fmax(dx, dy);
	increment_x = dx / steps; //increments each axis to know which points to draw
	increment_y = dy / steps;
	while (++i < steps) //to draw the points between the start (p1) and end (p2) point
	{
		mlx_put_pixel(image, pj->pic_x, pj->pic_y, get_rgba(165, 51, 255, 255));
		if (ray->rx < pj->x)
			pj->pic_x -= increment_x;
		else
			pj->pic_x += increment_x;
		if (ray->ry < pj->y)
			pj->pic_y -= increment_y;
		else
			pj->pic_y += increment_y;
	}
}
