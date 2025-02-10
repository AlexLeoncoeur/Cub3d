/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:15:02 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/10 16:30:41 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	draw_background(t_game_core *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 1280)
	{
		j = -1;
		while (++j < 720)
		{
			if (j < 360)
				mlx_put_pixel(game->img, i, j, get_rgba(51, 255, 227, 255));
			else
				mlx_put_pixel(game->img, i, j, get_rgba(213, 189, 82, 255));
		}
	}
}

static void	ft_refresh_half_screen(t_game_core *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < 720)
	{
		j = 0;
		while (j < 1280)
		{
			mlx_put_pixel(game->img, j, i, 0);
			j++;
		}
		i++;
	}
}

static void	ft_draw_square(t_game_core *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 16)
		{
			if ((i == 0 || i == 16) || (j == 0 || j == 16))
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
	ft_refresh_half_screen(game);
	draw_background(game);
	draw_rays(game);
	while (i < 33)
	{
		j = 0;
		while (j < 5)
		{
			if (game->data->map[j][i] == '1' || game->data->map[j][i] == ' ')
				ft_draw_square(game, i * 16, j * 16, get_rgba(0, 0, 0, 255));
			else if (game->data->map[j][i] == '0')
				ft_draw_square(game, i * 16, j * 16,
					get_rgba(255, 255, 255, 255));
			j++;
		}
		i++;
	}
	ft_draw_player(game, game->img);
}
