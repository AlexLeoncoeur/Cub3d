/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:04:50 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/10 16:30:41 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_wall_thickness(mlx_image_t *image, t_wall *wall)
{
	int	i;

	i = -1;
	while (++i < wall->thick)
	{
		mlx_put_pixel(image, wall->x + wall->x_offset + i, wall->y + wall->y_offset, get_rgba(51, 255, 54, 255));
	}
}

static void	draw_wall_lines(mlx_image_t *image, t_ray *ray, t_wall *wall, int i)
{
	float	dx;
	float	dy;
	float	steps;
	float	increment_x;
	float	increment_y;

	wall->x = ray->rx;
	wall->y = 0;
	dx = fabs(ray->rx - wall->x);
	dy = fabs((wall->lineheight) - wall->y);
	steps = fmax(dx, dy);
	increment_x = dx / steps; //increments each axis to know which points to draw
	increment_y = dy / steps;
	while (++i < steps)//to draw the points between the start (p1) and end (p2) point
	{
		wall->thick = 4;
		ft_wall_thickness(image, wall);
		if (ray->rx < wall->x)
			wall->x -= increment_x;
		else
			wall->x += increment_x;
		if (wall->lineheight < wall->y)
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
	ray->a_cos = ray->rangle - game->pj->pangle ;
	if (ray->a_cos < 0)
		ray->a_cos += 2 * PI;
	if (ray->a_cos >= 2 * PI)
		ray->a_cos -= 2 * PI;
	ray->total_dis = ray->total_dis * cos(ray->a_cos);
	wall->lineheight = (16 * game->data->height) / ray->total_dis / (1280 / 720); //cube size * wall desired height. Distance to wall changes size
	if (wall->lineheight > game->data->height - 1)
		wall->lineheight = game->data->height - 1;
	wall->x_offset = (ray->rx - 1280) * -1 + (ray->count * 4);//(ray->count * 2);//(ray->count * 4 + 530) / 2; 
	wall->y_offset = 360 - (wall->lineheight / 2);
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
	while (++i < steps && pj->pic_x > 0 && pj->pic_x < 1280 && pj->pic_y > 0 && pj->pic_y < 720) //to draw the points between the start (p1) and end (p2) point
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
