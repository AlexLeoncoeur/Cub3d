/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:15:02 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/14 15:54:29 by aarenas-         ###   ########.fr       */
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
	int			z;

	i = 0;
	j = 0;
	z = 0;
	game = (t_game_core *)param;
	while (game->map[z] != '\0')
	{
		if (game->map[z] == '\n')
		{
			j += 64;
			i = 0;
			z++;
		}
		if (game->map[z] == '1')
			ft_draw_square(game, i, j, get_rgba(0, 0, 0, 255));
		else if (game->map[z] == '0')
			ft_draw_square(game, i, j, get_rgba(255, 255, 255, 255));
		z++;
		i += 64;
	}
	ft_draw_player(game, game->img, game->pj->x, game->pj->y);
}

void	ft_map(t_game_core *game)
{
	game->map = "11111111\n10100001\n10100001\n10100001\n10000001\n10000101\n10000001\n11111111\0";
}
