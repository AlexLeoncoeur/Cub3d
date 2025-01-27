/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:52:39 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/27 16:05:00 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_horizontal_lines(t_game_core *game, t_ray *ray)
{
	float	atan;

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
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->dis_h = ft_distance(game, ray->hx, ray->hy);
			ray->dof = 8;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof++;
		}
	}
}

static void	ft_vertical_lines(t_game_core *game, t_ray *ray)
{
	float	ntan;

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
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->dis_v = ft_distance(game, ray->vx, ray->vy);
			ray->dof = 8;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof++;
		}
	}
}

void	draw_rays(t_game_core *game)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit(1);
	ray->hx = ray->rx;
	ray->hy = ray->ry;
	ray->rangle = game->pj->pangle - (DR * 45);
	if (ray->rangle < 0)
		ray->rangle += 2 * PI;
	if (ray->rangle > 2 * PI)
		ray->rangle -= 2 * PI;
	ray->count = 0;
	while (ray->count < 180)
	{
		ray->dof = 0;
		ray->dis_h = 1000000;
		ft_horizontal_lines(game, ray);
		ray->dis_v = 1000000;
		ray->dof = 0;
		ray->vx = ray->rx;
		ray->vy = ray->ry;
		ft_vertical_lines(game, ray);
		if (ray->dis_v < ray->dis_h)
		{
			ray->rx = ray->vx;
			ray->ry = ray->vy;
		}
		else if (ray->dis_v > ray->dis_h)
		{
			ray->ry = ray->hy;
			ray->rx = ray->hx;
		}
		draw_ray_line(game->img, game->pj, ray, -1);
		ray->rangle += DR / 2;
		if (ray->rangle < 0)
			ray->rangle += 2 * PI;
		if (ray->rangle > 2 * PI)
			ray->rangle -= 2 * PI;
		ray->count++;
	}
}
