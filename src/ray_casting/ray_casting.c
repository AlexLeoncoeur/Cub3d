/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:52:39 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/21 18:01:19 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == 1)
	{
		printf("Error: gettimeofday() failed\n");
		exit(1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static float	ft_distance(t_game_core *game, float end_x, float end_y)
{
	return (sqrt((end_x - game->pj->x) * (end_x - game->pj->x) + (end_y - game->pj->y) * (end_y - game->pj->y)));
}

static void	draw_line(mlx_image_t *image, t_player *pj, t_ray *ray)
{
	float	dx;
	float	dy;
	float	steps;
	float	increment_x;
	float	increment_y;
	float	x;
	float	y;
	int		i;

	i = 0;
	x = pj->x;
	y = pj->y;
	dx = fabs(ray->rx - x);
	dy = fabs(ray->ry - y);
	steps = fmax(dx, dy);
	increment_x = dx / steps; //increments each axis to know which points to draw
	increment_y = dy / steps;
	while (i < steps) //to draw the points between the start (p1) and end (p2) point
	{
		mlx_put_pixel(image, x, y, get_rgba(165, 51, 255, 255));
		if (ray->rx < pj->x)
			x -= increment_x;
		else
			x += increment_x;
		if (ray->ry < pj->y)
			y -= increment_y;
		else
			y += increment_y;
		i++;
	}
}

void	draw_rays(t_game_core *game)
{
	t_ray	*ray;
	float	atan;
	float	ntan;
	float	dis_h;
	float	hx;
	float	hy;
	float	dis_v;
	float	vx;
	float	vy;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit(1);
	dis_h = 1000000;
	hx = ray->rx;
	hy = ray->ry;
	ray->rangle = game->pj->pangle - DR * 45;
	if (ray->rangle < 0)
		ray->rangle += 2 * PI;
	if (ray->rangle > 2 * PI)
		ray->rangle -= 2 * PI;
	ray->count = 0;
	while (ray->count < 90)
	{
		// -- Horizontal lines -- //
		ray->dof = 0;
		atan = -1 / tan(ray->rangle);
		if (ray->rangle > PI) //Looking down
		{
			ray->ry = (((int)game->pj->y >> 6) << 6) - 0.0001;
			ray->rx = (game->pj->y - ray->ry) * atan + game->pj->x;
			ray->yo = -64;
			ray->xo = -ray->yo * atan;
		}
		if (ray->rangle < PI) //Looking up
		{
			ray->ry = (((int)game->pj->y >> 6) << 6) + 64;
			ray->rx = (game->pj->y - ray->ry) * atan + game->pj->x;
			ray->yo = 64;
			ray->xo = -ray->yo * atan;
		}
		if (ray->rangle == 0 || ray->rangle == PI) //Looking straight left or right
		{
			ray->rx = game->pj->x;
			ray->ry = game->pj->y;
			ray->dof = 8;
		}
		while (ray->dof < 8 && ray->rx < game->xh_limit && ray->ry < game->yh_limit && ray->rx > 0 && ray->ry > 0) //max of cubes we check
		{
			ray->mx = (int)ray->rx >> 6;
			ray->my = (int)ray->ry >> 6;
			ray->mp = ray->my * 8 + ray->mx; //8 is the x-size of the map
			if (ray->mp > 0 && ray->mp < 8 * 8 && game->map[ray->mx][ray->my] == 1)
			{
				hx = ray->rx;
				hy = ray->ry;
				dis_h = ft_distance(game, hx, hy);
				ray->dof = 8;
			}
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof++;
			}
		}
		// -- Vertical lines -- //
		dis_v = 1000000;
		vx = ray->rx;
		vy = ray->ry;
		ray->dof = 0;
		ntan = -tan(ray->rangle);
		if (ray->rangle > PI / 2 && ray->rangle < 3 * PI / 2) //Looking left
		{
			ray->rx = (((int)game->pj->x >> 6) << 6) - 0.0001;
			ray->ry = (game->pj->x - ray->rx) * ntan + game->pj->y;
			ray->xo = -64;
			ray->yo = -ray->xo * ntan;
		}
		if (ray->rangle < PI / 2 || ray->rangle > 3 * PI / 2) //Looking right
		{
			ray->rx = (((int)game->pj->x >> 6) << 6) + 64;
			ray->ry = (game->pj->x - ray->rx) * ntan + game->pj->y;
			ray->xo = 64;
			ray->yo = -ray->xo * ntan;
		}
		if (ray->rangle == 0 || ray->rangle == PI) //Looking straight up or down
		{
			ray->rx = game->pj->x;
			ray->ry = game->pj->y;
			ray->dof = 8;
		}
		while (ray->dof < 8 && ray->ry > game->yv_limit && ray->rx > game->xv_limit && ray->ry > 0 && ray->rx > 0) //max of cubes we check
		{
			ray->mx = (int)ray->rx >> 6;
			ray->my = (int)ray->ry >> 6;
			ray->mp = ray->my * 8 + ray->mx; //8 is the x-size of the map
			if (ray->mp > 0 && ray->mp < 8 * 8 && game->map[ray->mx][ray->my] == 1)
			{
				vx = ray->rx;
				vy = ray->ry;
				dis_v = ft_distance(game, vx, vy);
				ray->dof = 8;
			}
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof++;
			}
		}
		if (dis_v < dis_h)
		{
			ray->rx = vx;
			ray->ry = vy;
		}
		else if (dis_v > dis_h)
		{
			ray->ry = hy;
			ray->rx = hx;
		}
		draw_line(game->img, game->pj, ray);
		ray->rangle += DR;
		if (ray->rangle < 0)
			ray->rangle += 2 * PI;
		if (ray->rangle > 2 * PI)
			ray->rangle -= 2 * PI;
		ray->count++;
	}
}
