/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:25:42 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/13 15:27:49 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_up(t_game_core *game)
{
	int	x;
	int	y;
	int	next;

	x = game->pj->x;
	y = game->pj->y;
	next = (game->pj->y - 5);
	game->pj->y = next;
}

void	move_down(t_game_core *game)
{
	int	x;
	int	y;
	int	next;

	x = game->pj->x;
	y = game->pj->y;
	next = (game->pj->y + 5);
	game->pj->y = next;
}

void	move_left(t_game_core *game)
{
	int	x;
	int	y;
	int	next;

	x = game->pj->x;
	y = game->pj->y;
	next = (game->pj->x - 5);
	game->pj->x = next;
}

void	move_right(t_game_core *game)
{
	int	x;
	int	y;
	int	next;

	x = game->pj->x;
	y = game->pj->y;
	next = (game->pj->x + 5);
	game->pj->x = next;
}
