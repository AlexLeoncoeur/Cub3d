/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:52:39 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/15 16:28:12 by aarenas-         ###   ########.fr       */
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

void	draw_rays(t_game_core *game)
{
	t_ray	*ray;
	float	atan;

	ray->rangle = game->pj->pangle;
	ray->count = 0;
	while (ray->count < 1)
	{
		/* -- Horizontal lines -- */
		ray->dof = 0;
		atan = -1 / tan(ray->rangle);
		if (ray->rangle > PI) //Looking down
			ray
		ray->count++;
	}
}
