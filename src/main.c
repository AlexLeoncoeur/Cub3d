/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarenas- <aarenas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:31:09 by aarenas-          #+#    #+#             */
/*   Updated: 2025/02/18 17:28:43 by aarenas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	ft_check_cub(char *name)
{
	char	*aux;

	aux = name;
	while (*aux)
		aux++;
	while (name < aux)
	{
		if (*aux == '.')
			if (*aux + 1 && *aux + 2 && *aux + 3)
				if (aux[1] == 'c' && aux[2] == 'u' && aux[3] == 'b' && !aux[4])
					return (1);
		aux--;
	}
	return (0);
}

static void	xo_yo_fix(t_player *pj)
{
	if (pj->pdx < 0)
		pj->xo -= 20;
	else
		pj->xo = 20;
	if (pj->pdy < 0)
		pj->yo -= 20;
	else
		pj->yo = 20;
	pj->mpx = pj->x / 16;
	pj->mpx_plus_xo = (pj->x + pj->xo) / 16;
	pj->mpx_minus_xo = (pj->x - pj->xo) / 16;
	pj->mpy = pj->y / 16;
	pj->mpy_plus_yo = (pj->y + pj->yo) / 16;
	pj->mpy_minus_yo = (pj->y - pj->yo) / 16;
}

void	ft_controls_hook(mlx_key_data_t keydata, void *param)
{
	t_game_core	*game;

	game = (t_game_core *)param;
	xo_yo_fix(game->pj);
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
		if (keydata.key == MLX_KEY_LEFT)
			turn_left(game);
		if (keydata.key == MLX_KEY_RIGHT)
			turn_right(game);
		if (keydata.key == MLX_KEY_A)
			move_left(game);
		if (keydata.key == MLX_KEY_D)
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
	mlx_image_t	*image;

	i = game->pj->x;
	j = game->pj->y;
	image = img;
	draw_pj(game->img, game->pj, -1);
	i = -4;
	while (i < 4)
	{
		j = -4;
		while (j < 4)
		{
			mlx_put_pixel(image, game->pj->x + i, game->pj->y + j,
				get_rgba(51, 255, 246, 255));
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data			data;
	mlx_image_t		*img;
	t_game_core		*game;
	t_player		*pj;

	(void)argc;
	ft_init(&data, argv[1]);
	if (argc != 2)
		ft_errors(&data, ERR_ARGC, NULL);
	if (ft_check_cub(argv[1]) != 1)
		ft_errors(&data, ERR_EXT, NULL);
	game = malloc(sizeof(t_game_core));
	pj = malloc(sizeof(t_player));
	if (!game || !pj)
		exit(EXIT_FAILURE);
	game->id = data.mlx;
	game->data = &data;
	img = data.img;
	game->spaces = 8;
	mlx_resize_hook(game->id, ft_resize, NULL);
	ft_init_data_pj(game, pj, img);
	mlx_loop_hook(game->id, &ft_draw_2d, game);
	mlx_key_hook(game->id, &ft_controls_hook, game);
	mlx_loop(game->id);
	mlx_terminate(game->id);
	return (0);
}
