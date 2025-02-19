/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcallejo <jcallejo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:15:02 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/19 13:10:26 by jcallejo         ###   ########.fr       */
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
	while (++i < game->data->width)
	{
		j = -1;
		while (++j < game->data->height)
		{
			if (j < (game->data->height / 2))
				mlx_put_pixel(game->img, i, j, game->data->sky);
			else
				mlx_put_pixel(game->img, i, j, game->data->floor);
		}
	}
}

static void	ft_refresh_half_screen(t_game_core *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->data->height)
	{
		j = 0;
		while (j < game->data->width)
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

	i = -1;
	game = (t_game_core *)param;
	ft_refresh_half_screen(game);
	draw_background(game);
	draw_rays(game);
	while (++i < 33)
	{
		j = -1;
		while (++j < game->data->map_rows)
		{
			if (game->data->map[j][i] == '1' || game->data->map[j][i] == ' ')
				ft_draw_square(game, i * 16, j * 16, get_rgba(0, 0, 0, 255));
			else if (game->data->map[j][i] == '0' || game->data->map[j][i] == 'S'|| game->data->map[j][i] == 'E' || game->data->map[j][i] == 'W' || game->data->map[j][i] == 'N')
			{
				ft_draw_square(game, i * 16, j * 16,
					get_rgba(255, 255, 255, 255));
			}
		}
	}
	ft_draw_player(game, game->img);
	ft_animations(game->data);
}
