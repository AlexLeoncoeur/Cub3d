/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:36:27 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/27 14:55:31 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	ft_distance(t_game_core *game, float end_x, float end_y)
{
	return (sqrt((end_x - game->pj->x) * (end_x - game->pj->x)
			+ (end_y - game->pj->y) * (end_y - game->pj->y)));
}

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

void	ft_init_data_pj(t_game_core *data, t_player *pj, mlx_image_t *img)
{
	pj->x = 256;
	pj->y = 256;
	data->pj = pj;
	data->img = img;
	data->xh_limit = 1024;
	data->yh_limit = 512;
	data->xv_limit = 0;
	data->yv_limit = 0;
	data->last_time = ft_get_time();
	data->delay = 33;
	data->pj->pangle = 6.28;
	ft_map(data);
}
