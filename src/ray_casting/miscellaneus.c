/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:36:27 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/06 13:13:39 by aarenas-         ###   ########.fr       */
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

void	ft_init_data_pj(t_game_core *game, t_player *pj, mlx_image_t *img)
{
	pj->x = game->data->player->start_x * 16;
	pj->y = game->data->player->start_y * 16;
	game->pj = pj;
	game->img = img;
	game->xh_limit = game->data->width;
	game->yh_limit = game->data->width;
	game->xv_limit = 0;
	game->yv_limit = 0;
	game->last_time = ft_get_time();
	game->delay = 33;
	game->pj->pangle = 6.28;
}
