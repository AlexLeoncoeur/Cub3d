/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:36:27 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/27 12:40:04 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
