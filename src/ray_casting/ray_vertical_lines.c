/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_vertical_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:55:59 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/30 15:20:51 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_check_cube_hit(t_game_core *game, t_ray *ray)
{
	while (ray->dof < 8 && ray->ry > 0 && ray->rx > 0) //max of cubes we check
	{
		ray->mx = (int)ray->rx >> 6;
		ray->my = (int)ray->ry >> 6;
		ray->mp = ray->my * 8 + ray->mx; //8 is the x-size of the map
		if (ray->mp > 0 && ray->mp < 8 * 8 && game->data->map[ray->mx][ray->my] == 1)
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

static void	ft_looking_straight_up_down(t_game_core *game, t_ray *ray)
{
	if (ray->rangle == 0 || ray->rangle == PI)
	{
		ray->rx = game->pj->x;
		ray->ry = game->pj->y;
		ray->dof = 8;
	}
}

static void	ft_looking_left_right(t_game_core *game, t_ray *ray)
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
}

void	ft_vertical_lines(t_game_core *game, t_ray *ray)
{
	ft_looking_left_right(game, ray);
	ft_looking_straight_up_down(game, ray);
	ft_check_cube_hit(game, ray);
}
