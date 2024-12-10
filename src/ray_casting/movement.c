/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:25:42 by aarenas-          #+#    #+#             */
/*   Updated: 2024/12/10 16:50:13 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_up(t_game_core *game)
{
	int	x;
	int	y;
	int	next;

	x = game->pj->x * (32);
	y = game->pj->y * (32);
	next = (game->pj->y - 1) * (32);
}

void	move_down(t_game_core *game)
{
	int	x;
	int	y;
	int	next;

	x = game->pj->x * (32);
	y = game->pj->y * (32);
	next = (game->pj->y + 1) * (32);
}

void	move_left(t_game_core *game)
{
	int	x;
	int	y;
	int	next;

	x = game->pj->x * (32);
	y = game->pj->y * (32);
	next = (game->pj->x - 1) * (32);
}

void	move_right(t_game_core *game)
{
	int	x;
	int	y;
	int	next;

	x = game->pj->x * (32);
	y = game->pj->y * (32);
	next = (game->pj->x + 1) * (32);
}
