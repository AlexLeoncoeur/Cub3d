/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_norm_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:26 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/21 13:48:49 by jcallejo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	check_valid_pos(char c)
{
	if (c == 'S' || c == 'W' || c == 'N' || c == 'E' || c == '0')
		return (1);
	return (0);
}

void	ft_delete(t_game_core *game)
{
	free(game->id);
	free(game->img);
	free(game->pj);
}
