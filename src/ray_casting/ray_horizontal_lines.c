/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_horizontal_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:37:54 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/06 15:23:53 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_check_cube_hit(t_game_core *game, t_ray *ray)
{
	while (ray->dof < 5 && ray->rx > 0 && ray->ry > 0 && ray->rx < 1280 && ray->ry < 720) //max of cubes we check
	{
		ray->mx = (int)ray->rx >> 4;
		ray->my = (int)ray->ry >> 4;
		ray->mp = ray->my * 25 + ray->mx; //8 is the x-size of the map
		if (ray->mp > 0 && ray->mp < 25 * 5 && game->data->map[ray->my][ray->mx] == '1')
		{
			ray->hx = ray->rx;
			ray->hy = ray->ry;
			ray->dis_h = ft_distance(game, ray->hx, ray->hy);
			ray->dof = 5;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof++;
		}
	}
}

static void	ft_looking_straight_left_right(t_game_core *game, t_ray *ray)
{
	if (ray->rangle == 0 || ray->rangle == PI) //Looking straight left or right
	{
		ray->rx = game->pj->x;
		ray->ry = game->pj->y;
		ray->dof = 5;
	}
}

static void	ft_looking_up_down(t_game_core *game, t_ray *ray)
{
	float	atan;

	atan = -1 / tan(ray->rangle);
	if (ray->rangle > PI) //Looking down
	{
		ray->ry = (((int)game->pj->y >> 4) << 4) - 0.0001;
		ray->rx = (game->pj->y - ray->ry) * atan + game->pj->x;
		ray->yo = -16;
		ray->xo = -ray->yo * atan;
	}
	if (ray->rangle < PI) //Looking up
	{
		ray->ry = (((int)game->pj->y >> 4) << 4) + 16;
		ray->rx = (game->pj->y - ray->ry) * atan + game->pj->x;
		ray->yo = 16;
		ray->xo = -ray->yo * atan;
	}
}

void	ft_horizontal_lines(t_game_core *game, t_ray *ray)
{
	ft_looking_up_down(game, ray);
	ft_looking_straight_left_right(game, ray);
	ft_check_cube_hit(game, ray);
}
