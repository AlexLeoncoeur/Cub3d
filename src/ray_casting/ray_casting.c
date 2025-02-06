/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:52:39 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/06 16:44:21 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ft_restart_angle(t_ray *ray)
{
	if (ray->rangle < 0)
		ray->rangle += 2 * PI;
	if (ray->rangle > 2 * PI)
		ray->rangle -= 2 * PI;
}

static void	ft_next_ray_dir(t_ray *ray)
{
	ray->rangle += DR / 4;
	if (ray->rangle < 0)
		ray->rangle += 2 * PI;
	if (ray->rangle > 2 * PI)
		ray->rangle -= 2 * PI;
}

static void	ft_shortest_ray(t_ray *ray)
{
	if (ray->dis_v < ray->dis_h)
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->total_dis = ray->dis_v;
	}
	else if (ray->dis_v > ray->dis_h)
	{
		ray->ry = ray->hy;
		ray->rx = ray->hx;
		ray->total_dis = ray->dis_h;
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
	ray->rangle = game->pj->pangle - (DR * 30);
	ft_restart_angle(ray);
	ray->count = 0;
	while (ray->count < 240)
	{
		ray->dof = 0;
		ray->dis_h = 1000000;
		ft_horizontal_lines(game, ray);
		ray->dis_v = 1000000;
		ray->dof = 0;
		ray->vx = ray->rx;
		ray->vy = ray->ry;
		ft_vertical_lines(game, ray);
		ft_shortest_ray(ray);
		draw_ray_line(game->img, game->pj, ray, -1);
		ft_manage_3d_walls(game, ray);
		ft_next_ray_dir(ray);
		ray->count++;
	}
		//funcion para borrar ray
}
