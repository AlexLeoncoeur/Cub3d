/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:15:02 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/21 14:12:51 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	ft_draw_square(t_game_core *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if ((i == 0 || i == 64) || (j == 0 || j == 64))
				mlx_put_pixel(game->img, x + i, y + j, 0);
			else
				mlx_put_pixel(game->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_2d(void *param)
{
	t_game_core	*game;
	int			i;
	int			j;

	i = 0;
	game = (t_game_core *)param;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (game->map[i][j] == 1)
				ft_draw_square(game, i * 64, j * 64, get_rgba(0, 0, 0, 255));
			else if (game->map[i][j] == 0)
				ft_draw_square(game, i * 64, j * 64, get_rgba(255, 255, 255, 255));
			j++;
		}
		i++;
	}
	ft_draw_player(game, game->img, game->pj->x, game->pj->y);
	draw_rays(game);
}

void	ft_map(t_game_core *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (i == 0 || i == 7)
				game->map[i][j] = 1;
			else if (j == 0 || j == 7)
				game->map[i][j] = 1;
			else if ((i == 2 && j == 1) || (i == 2 && j == 2) || (i == 2 && j == 3) || (i == 5 && j == 5))
				game->map[i][j] = 1;
			else
				game->map[i][j] = 0;
			j++;
		}
		i++;
	}
}
