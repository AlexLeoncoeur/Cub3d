/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:56:25 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/14 12:42:57 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_controls_hook(mlx_key_data_t keydata, void *param)
{
	t_game_core	*game;

	game = (t_game_core *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			exit(0); //funcion para liberar memoria
			mlx_close_window(game->id);
		}
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			move_up(game);
		if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			move_down(game);
		if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			move_left(game);
		if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			move_right(game);
	}
}

void	ft_resize(int width, int height, void *param)
{
	(void)param;
	(void)width;
	(void)height;
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
}

void	ft_draw_player(mlx_image_t *img, int pj_x, int pj_y)
{
	int	i;
	int	j;

	i = -4;
	while (i < 4)
	{
		j = -16;
		while (j < 16)
		{
			mlx_put_pixel(img, pj_x + i, pj_y + j, get_rgba(200, 0, 255, 255));
			j++;
		}
		i++;
	}
	i = -16;
	while (i < 16)
	{
		j = 8;
		while (j < 16)
		{
			mlx_put_pixel(img, pj_x + i, pj_y + j, get_rgba(200, 0, 255, 255));
			j++;
		}
		i++;
	}
}

/* void	ft_draw_pixels(void *param)
{
	int			x;
	int			y;
	t_game_core	*game;

	x = 0;
	y = 0;
	game = (t_game_core *)param;
	game->current_time = ft_get_time();
	if (game->current_time - game->last_time >= game->delay)
	{
		game->last_time = game->current_time;
		while (y < game->y_limit)
		{
			x = 0;
			while (x < game->x_limit)
			{
				mlx_put_pixel(game->img, x, y, 0);
				x++;
			}
			y++;
		}
		ft_draw_player(game->img, game->pj->x, game->pj->y);
	}
} */

int	main(void)
{
	mlx_t			*id;
	mlx_image_t		*img;
	t_game_core		*data;
	t_player		*pj;

	id = mlx_init(1024, 512, "cub3d", true);
	data = malloc(sizeof(t_game_core));
	pj = malloc(sizeof(t_player));
	if (!id || !data || !pj)
		exit(EXIT_FAILURE);
	img = mlx_new_image(id, 1024, 512);
	mlx_image_to_window(id, img, 0, 0);
	mlx_resize_hook(id, ft_resize, NULL);
	pj->x = 256;
	pj->y = 256;
	data->pj = pj;
	data->img = img;
	data->x_limit = 1024;
	data->y_limit = 512;
	data->last_time = ft_get_time();
	data->delay = 33;
	ft_map(data);
	mlx_loop_hook(id, &ft_draw_2d, data);
	mlx_key_hook(id, &ft_controls_hook, data);
	mlx_loop(id);
	mlx_terminate(id);
	return (0);
}
/* -- to do -- */

/* Hacer una funcion para refrescar
la pantalla y que se vea al muñeco moverse */

	//t_game_core		*data; //estructura con datos del mapa y juego

	/* if (!id)
		ft_error_exit("Error: Could not initialize identifier\n"); */