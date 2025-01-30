/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:56:25 by aarenas-          #+#    #+#             */
/*   Updated: 2025/01/27 14:21:19 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//Algoritmo de Bresenham
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

void	ft_draw_player(t_game_core *game, mlx_image_t *img)
{
	int			i;
	int			j;
	int			z;
	mlx_image_t	*image;

	z = game->pj->pdx;
	i = game->pj->x;
	j = game->pj->y;
	image = img;
	draw_pj(game->img, game->pj, -1);
	i = -8;
	while (i < 8)
	{
		j = -8;
		while (j < 8)
		{
			mlx_put_pixel(image, game->pj->x + i, game->pj->y + j,
				get_rgba(51, 255, 246, 255));
			j++;
		}
		i++;
	}
}

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
	ft_init_data_pj(data, pj, img);
	mlx_loop_hook(id, &ft_draw_2d, data);
	mlx_key_hook(id, &ft_controls_hook, data);
	mlx_loop(id);
	mlx_terminate(id);
	return (0);
}
