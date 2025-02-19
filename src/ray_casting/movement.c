/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:25:42 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/19 17:56:34 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_up(t_game_core *game)
{
	if (game->data->map[(int)(game->pj->y + game->pj->pdy) / 16]
		[(int)(game->pj->x + game->pj->pdx) / 16] == '0')
	{
		game->pj->y += game->pj->pdy * game->data->player->m_speed;
		game->pj->x += game->pj->pdx * game->data->player->m_speed;
	}
}

void	move_down(t_game_core *game)
{
	if (game->data->map[(int)(game->pj->y - game->pj->pdy) / 16]
		[(int)(game->pj->x - game->pj->pdx) / 16] == '0')
	{
		game->pj->y -= game->pj->pdy * game->data->player->m_speed;
		game->pj->x -= game->pj->pdx * game->data->player->m_speed;
	}
}

void	move_left(t_game_core *game)
{
	if (game->data->map[(int)(game->pj->y - game->pj->pdx) / 16]
		[(int)(game->pj->x + game->pj->pdy) / 16] == '0')
	{
		game->pj->x += sin(game->pj->pangle) * 5 * game->data->player->m_speed;
		game->pj->y -= cos(game->pj->pangle) * 5 * game->data->player->m_speed;
	}
}

void	move_right(t_game_core *game)
{
	if (game->data->map[(int)(game->pj->y + game->pj->pdx) / 16]
		[(int)(game->pj->x - game->pj->pdy) / 16] == '0')
	{
		game->pj->x -= sin(game->pj->pangle) * 5 * game->data->player->m_speed;
		game->pj->y += cos(game->pj->pangle) * 5 * game->data->player->m_speed;
	}
}
