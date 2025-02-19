/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:25:42 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/19 11:24:33 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_up(t_game_core *game)
{
	if (game->data->map[(int)(game->pj->y + game->pj->pdy) / 16]
		[(int)(game->pj->x + game->pj->pdx) / 16] == '0')
	{
		game->pj->y += game->pj->pdy * game->data->player->movespeed;
		game->pj->x += game->pj->pdx * game->data->player->movespeed;
	}
}

void	move_down(t_game_core *game)
{
	if (game->data->map[(int)(game->pj->y - game->pj->pdy) / 16]
		[(int)(game->pj->x - game->pj->pdx) / 16] == '0')
	{
		game->pj->y -= game->pj->pdy * game->data->player->movespeed;
		game->pj->x -= game->pj->pdx * game->data->player->movespeed;
	}
}

void	move_left(t_game_core *game)
{
	if (game->data->map[(int)(game->pj->y - game->pj->pdx) / 16]
		[(int)(game->pj->x + game->pj->pdy) / 16] == '0')
	{
		game->pj->x += sin(game->pj->pangle) * 5 * game->data->player->movespeed;
		game->pj->y -= cos(game->pj->pangle) * 5 * game->data->player->movespeed;
	}
}

void	move_right(t_game_core *game)
{
	if (game->data->map[(int)(game->pj->y + game->pj->pdx) / 16]
		[(int)(game->pj->x - game->pj->pdy) / 16] == '0')
	{
		game->pj->x -= sin(game->pj->pangle) * 5 * game->data->player->movespeed;
		game->pj->y += cos(game->pj->pangle) * 5 * game->data->player->movespeed;
	}
}

void	turn_left(t_game_core *game)
{
	game->pj->pangle -= 0.1;
	if (game->pj->pangle < 0)
		game->pj->pangle += 2 * PI;
	game->pj->pdx = cos(game->pj->pangle) * 5;
	game->pj->pdy = sin(game->pj->pangle) * 5;
}

void	turn_right(t_game_core *game)
{
	game->pj->pangle += 0.1;
	if (game->pj->pangle > 2 * PI)
		game->pj->pangle -= 2 * PI;
	game->pj->pdx = cos(game->pj->pangle) * 5;
	game->pj->pdy = sin(game->pj->pangle) * 5;
}
