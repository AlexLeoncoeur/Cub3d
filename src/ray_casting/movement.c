/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:25:42 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/10 18:01:40 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_up(t_game_core *game)
{
	if (game->data->map[(int)(game->pj->y + game->pj->pdy) / 16][(int)(game->pj->x + game->pj->pdx) / 16] == '0')
	{
		game->pj->y += game->pj->pdy;
		game->pj->x += game->pj->pdx;
	}
}

void	move_down(t_game_core *game)
{
	game->pj->y -= game->pj->pdy;
	game->pj->x -= game->pj->pdx;
}

void	move_left(t_game_core *game)
{
	game->pj->x += sin(game->pj->pangle) * 5;
	game->pj->y -= cos(game->pj->pangle) * 5;
}

void	move_right(t_game_core *game)
{
	game->pj->x -= sin(game->pj->pangle) * 5;
	game->pj->y += cos(game->pj->pangle) * 5;
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
