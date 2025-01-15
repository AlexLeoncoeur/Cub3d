/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:52:39 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/15 17:48:44 by aarenas-         ###   ########.fr       */
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

	ray = malloc(sizeof(t_ray));
	if (!ray)
		exit(1);
	ray->rangle = game->pj->pangle;
	ray->count = 0;
	while (ray->count < 1)
	{
		/* -- Horizontal lines -- */
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
		while (ray->dof < 8 && ray->rx < game->x_limit && ray->ry < game->y_limit && ray->rx > 0 && ray->ry > 0) //max of cubes we check
		{
			printf("rx: %f ry: %f\n", ray->rx, ray->ry);
			ray->mx = (int)ray->rx >> 6;
			ray->my = (int)ray->ry >> 6;
			ray->mp = ray->my * 8 + ray->mx; //8 is the x-size of the map
			if (ray->mp < 8 * 8 && game->map[ray->mp] == 1)
				ray->dof = 8;
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof++;
			}
		}
		draw_line(game->img, game->pj, ray);
		ray->count++;
	}
}
